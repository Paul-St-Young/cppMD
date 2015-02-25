#ifndef _MOMENTUMESTIMATOR_H
#define _MOMENTUMESTIMATOR_H

#include "Estimator.h"

class MomentumEstimator : public Estimator{
public:
    MomentumEstimator(ParticleSet pset) : Estimator(pset) {}; 
	PosType vectorEvaluate();
};

#endif
