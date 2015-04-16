#ifndef _METROPOLIS_H
#define _METROPOLIS_H

#include "Updator.h"
#include <random>

class Metropolis: public Updator {
std::mt19937* _mt;
std::normal_distribution<RealType>* _norm;
std::uniform_real_distribution<RealType> _uni; // default to (0,1)
int _accepted; // number of accepted moves
RealType _beta; // 1/kT
RealType _calcPotential(int i); // calculate the potential on particle i
public:
	Metropolis(ParticleSet* pset, ForceField* ff,SimulationBox* box,Thermostat* therm, RealType sig, RealType T);
	~Metropolis();
    void update();
    RealType acceptedSteps(){return _accepted;};
};

#endif
