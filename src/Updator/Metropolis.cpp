#include "Metropolis.h"

using namespace std;

Metropolis::Metropolis(ParticleSet* pset, ForceField* ff,SimulationBox* box,Thermostat* therm, RealType mu, RealType sig,RealType T):Updator(pset,ff,box,therm){

    random_device rd;
    _mt = new mt19937(rd());
    _norm = new normal_distribution<RealType>(mu,sig);
    
    _accepted=0;
    _beta = 1/T;

}

void Metropolis::update(){
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

Metropolis::~Metropolis(){
    delete _mt;
    delete _norm;
}
