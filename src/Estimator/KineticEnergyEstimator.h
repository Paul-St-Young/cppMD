#ifndef _KINETICENERGYESTIMATOR_H
#define _KINETICENERGYESTIMATOR_H

#include "Estimator.h"

class KineticEnergyEstimator : public Estimator{
public:
    KineticEnergyEstimator(ParticleSet pset) : Estimator(pset) {}; 
	virtual RealType scalarEvaluate();
};

#endif
