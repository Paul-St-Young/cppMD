#ifndef _STRUCTUREFACTORESTIMATOR_H
#define _STRUCTUREFACTORESTIMATOR_H

#include "Estimator.h"

#define _USE_MATH_DEFINES

#include <complex>
#include <cmath>

class StructureFactorEstimator : public Estimator{
ComplexType _rhoK(PosType k);
std::vector<PosType> _leagalKVecs(int maxK);
RealType _L;
int _maxK;
int _mystep;
public:
    std::vector<PosType> kVecs;
    std::vector<ComplexType> SK;
    
    StructureFactorEstimator(ParticleSet pset, RealType L, int maxK); 
	void accumulate(int t);
	void finalize(std::string filename);
};

#endif
