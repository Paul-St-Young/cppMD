#include "Metropolis.h"

using namespace std;

Metropolis::Metropolis(ParticleSet* pset, ForceField* ff, SimulationBox* box, Thermostat* therm, RealType sig, RealType T, bool useForce, RealType dt)
 : Updator(pset,ff,box,therm), _beta(1/T), _useForce(useForce), _dt(dt), _sigma(sig) {

    random_device rd;
    _mt = new mt19937(rd());
    _norm = new normal_distribution<RealType>(0,sig);
    
    _accepted=0;

}

void Metropolis::update(){
    if (!_useForce){
	    for (int i=0;i<_pset->n;i++){
	    // for each particle
	
	        // evaluate energy on this particle
	        RealType oldU=_calcPotential(i);
	
	        // try a move
	        PosType trialMove;
	        for (int coord=0;coord<_MD_DIM;coord++){
	            trialMove.push_back((*_norm)(*_mt)); // Gaussian move
                _pset->ptcls[i]->r[coord] += trialMove[coord];
            }
            
            // evaluate the new energy
            RealType newU=_calcPotential(i);
            
            // decide acceptance
            RealType A=exp(-_beta*(newU-oldU));   
            if (_uni(*_mt)<A){
                _accepted += 1;
            } else { // put back particle if rejected
                for (int coord=0;coord<_MD_DIM;coord++){
                    _pset->ptcls[i]->r[coord] -= trialMove[coord];
                }
            }
            
	    }
	} else _updateWithForce();
}

RealType Metropolis::_calcPotential(int i){
    RealType U=0;
    PosType dR;
    for (int j=0;j<_pset->n;j++){
        if (i!=j){
	        dR=_box->displacement(i,j);
	        U+=_ff->myPP()->potential(dR);
        }
    }
    return U;
}

RealType Metropolis::_updateWithForce(){

    PosType x,x1,xa,xa1;
    x.reserve(_MD_DIM);
    x1.reserve(_MD_DIM);
    xa.reserve(_MD_DIM);
    xa1.reserve(_MD_DIM);
    
    _ff->apply(); // fill in all acceleration
    
    for (int i=0;i<_pset->n;i++){
	// for each particle
	    
	    // evaluate energy on this particle
        RealType oldU=_calcPotential(i);
	    
	    // save old position and force bias
        for (int coord=0;coord<_MD_DIM;coord++){
            x[coord] = _pset->ptcls[i]->r[coord];
            xa[coord] = _pset->ptcls[i]->a[coord]/
                            2./_pset->ptcls[i]->m*pow(_dt,2);
        }
        
        // try a move
        PosType trialMove;
        for (int coord=0;coord<_MD_DIM;coord++){
            trialMove.push_back((*_norm)(*_mt));
            _pset->ptcls[i]->r[coord] += trialMove[coord]+xa[coord];
        }
        
        // evaluate the new energy
        RealType newU=_calcPotential(i);
        
        _ff->apply(i); // update the force on the moved particle
	    // save new position and force bias
        for (int coord=0;coord<_MD_DIM;coord++){
            x1[coord] = _pset->ptcls[i]->r[coord];
            xa1[coord] = _pset->ptcls[i]->a[coord]/
                            2./_pset->ptcls[i]->m*pow(_dt,2);
        }
        
        // calculate proposal ratio
        RealType lnT=0;
        for (int coord=0;coord<_MD_DIM;coord++){
            lnT += (x[coord]-x1[coord]+0.5*(xa[coord]-xa1[coord]))*(xa[coord]+xa1[coord]);
            lnT /= pow(_sigma,2);
        }
        
        // decide acceptance
        RealType lnA=-_beta*(newU-oldU)+lnT;
        if (_uni(*_mt)<exp(lnA)){
            _accepted += 1;
        } else { // put back particle if rejected
            for (int coord=0;coord<_MD_DIM;coord++){
                _pset->ptcls[i]->r[coord] -= trialMove[coord]+xa[coord];
            }
        }
        
    }
    
    
}

Metropolis::~Metropolis(){
    delete _mt;
    delete _norm;
}
