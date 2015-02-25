#ifndef _PAIRCORRELATIONESTIMATOR_H
#define _PAIRCORRELATIONESTIMATOR_H

#include "Estimator.h"
#include "../Simulation/SimulationBox.h"

class PairCorrelationEstimator : public Estimator{
SimulationBox* _box;
RealType _rmin,_rmax,_dr;
RealType _L;
public:
    PairCorrelationEstimator(ParticleSet pset, SimulationBox* box, RealType rmax, RealType dr, RealType L, RealType rmin=0.0) : Estimator(pset), _box(box), _rmin(rmin), _rmax(rmax), _L(L), _dr(dr){};
    
    PosType vectorEvaluate();
};
    
#endif
