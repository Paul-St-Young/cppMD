#ifndef _POTENTIALESTIMATOR_H
#define _POTENTIALESTIMATOR_H

#include "Estimator.h"
#include "../ForceField/PairPotential.h"
#include "../Simulation/SimulationBox.h"

class PotentialEstimator : public Estimator{
PairPotential* _pp;
SimulationBox* _box;
public:
    PotentialEstimator(ParticleSet pset, PairPotential* pp, SimulationBox* box) 
        : Estimator(pset), _pp(pp), _box(box) {}; 
	virtual RealType scalarEvaluate();
};

#endif
