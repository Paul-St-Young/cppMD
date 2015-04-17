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
	        PosType oldR;
	        for (int coord=0;coord<_MD_DIM;coord++) oldR.push_back( _pset->ptcls[i]->r[coord] ); 
	        RealType oldU=_calcPotential(i);
	
	        // try a move
	        for (int coord=0;coord<_MD_DIM;coord++){
                _pset->ptcls[i]->r[coord] += (*_norm)(*_mt); // Gaussian move
                _box->putInBox();
            }
            
            // evaluate the new energy
            RealType newU=_calcPotential(i);
            
            // decide acceptance
            RealType A=exp(-_beta*(newU-oldU));   
            if (_uni(*_mt)<A){
                _accepted += 1;
            } else { // put back particle if rejected
                for (int coord=0;coord<_MD_DIM;coord++){
                    _pset->ptcls[i]->r[coord] = oldR[coord];
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
      
    for (int i=0;i<_pset->n;i++){
	// for each particle
	
	    // save current position
	    PosType oldR;
        for (int coord=0;coord<_MD_DIM;coord++)
            oldR.push_back( _pset->ptcls[i]->r[coord] );
        
        // evaluate energy on this particle
        RealType oldU=_calcPotential(i);
	    
	    _ff->apply(i); // update the force on this particle
	    // save old position and force bias
        for (int coord=0;coord<_MD_DIM;coord++){
            x[coord] = _pset->ptcls[i]->r[coord];
            xa[coord] = 0.5*_pset->ptcls[i]->a[coord]*_dt*_dt;
        }
        
        // try a move with force bias
        PosType trialMove;
        for (int coord=0;coord<_MD_DIM;coord++){
            trialMove.push_back((*_norm)(*_mt)+xa[coord]);
            _pset->ptcls[i]->r[coord] += trialMove[coord];
        }
        _box->putInBox();
        
        // evaluate the new energy
        RealType newU=_calcPotential(i);
        
        _ff->apply(i); // update the force on the moved particle
	    // save new position and force bias
        for (int coord=0;coord<_MD_DIM;coord++){
            x1[coord] = _pset->ptcls[i]->r[coord];
            xa1[coord] = 0.5*_pset->ptcls[i]->a[coord]*_dt*_dt;
        }
        
        // calculate proposal ratio
        RealType lnT=0;
        PosType backTrialMove;
        for (int coord=0;coord<_MD_DIM;coord++){
            backTrialMove.push_back( x[coord]-x1[coord]-xa1[coord] );
            lnT += pow(trialMove[coord],2)-pow(backTrialMove[coord],2);
            lnT /= pow(_sigma,2);
        }
        
        // decide acceptance
        RealType lnA=-_beta*(newU-oldU);//+lnT;
        if (_uni(*_mt)<exp(lnA)){
            _accepted += 1;
        } else { // put back particle if rejected
            for (int coord=0;coord<_MD_DIM;coord++){
                _pset->ptcls[i]->r[coord] = oldR[coord];
            }
        }
        
    }
}

Metropolis::~Metropolis(){
    delete _mt;
    delete _norm;
}
