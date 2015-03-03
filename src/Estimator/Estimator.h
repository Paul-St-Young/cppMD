#ifndef _ESTIMATOR_H
#define _ESTIMATOR_H

#include "../Interface/TypeFactory.h"
#include "../Particle/ParticleSet.h"

#include <complex>

class Estimator{
protected:
    ParticleSet _pset;
public:
    Estimator(ParticleSet pset) : _pset(pset) {};
	virtual RealType scalarEvaluate(){};
	virtual PosType  vectorEvaluate(){};
	virtual void complexVectorAccumulate(){};
	virtual void writeFile(std::string filename){};
};

#endif
