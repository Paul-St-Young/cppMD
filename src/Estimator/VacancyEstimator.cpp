#include "VacancyEstimator.h"
VacancyEstimator::VacancyEstimator(ParticleSet pset,int nlattice, SimulationBox* box,std::string vacTraj) 
    : Estimator(pset), _nlattice(nlattice), _box(box), _vacTraj(vacTraj) {
    _latticeParticles = new ParticlePool(nlattice);
    _latticeParticles->initCubicPositions(box->L());
    _lattice = new ParticleSet(_latticeParticles->myParticles());
}; 

PosType VacancyEstimator::vectorEvaluate(){

    RealType maxDist = 0;
    RealType maxIdx = 0;
    for (int i=0;i<_lattice->n;i++){
    // for each lattice site, calculate its average distance to the particles
        RealType myDist=0;
        for (int j=0;j<_pset.n;j++){
            myDist += _box->distance(_lattice->ptcls[i]->r,_pset.ptcls[j]->r);
        }
        myDist /= (RealType) _pset.n;
        if (myDist>maxDist){
            maxDist = myDist;
            maxIdx = i;
        }
    }
    
    return _lattice->ptcls[maxIdx]->r;
}

VacancyEstimator::~VacancyEstimator(){
    delete _lattice;
    delete _latticeParticles;
}
