#ifndef _STRUCTUREFACTORESTIMATOR_H
#define _STRUCTUREFACTORESTIMATOR_H

#include "Estimator.h"

#define _USE_MATH_DEFINES

#include <complex>
#include <cmath>

class StructureFactorEstimator : public Estimator{
std::complex<RealType> _rhoK(PosType k);
std::vector<PosType> _leagalKVects(int maxK);
RealType _L;
int _maxK;
public:
    StructureFactorEstimator(ParticleSet pset, RealType L, int maxK) : Estimator(pset), _L(L), _maxK(maxK) {}; 
	RealType scalarEvaluate();
};

#endif
