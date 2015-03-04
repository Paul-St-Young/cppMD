#ifndef _VELOCITYCORRELATION_H
#define _VELOCITYCORRELATION_H

#include "Estimator.h"

class VelocityCorrelation : public Estimator{
int _tmax, _myt;
std::vector<RealType> _cv, _cvCur;
std::vector<PosType> _refVel;
public:
    VelocityCorrelation(ParticleSet pset, int tmax); 
	void accumulate(int t);
	void finalize(std::string filename);
};

#endif
