#ifndef _FORCEFIELD_H
#define _FORCEFIELD_H

#include "../Particle/ParticleSet.h"
#include "../Simulation/SimulationBox.h"
#include "PairPotential.h"

class ForceField{
ParticleSet* _pset;
PairPotential* _pp;
SimulationBox* _box;
public:
	ForceField(ParticleSet* pset, PairPotential* pp, SimulationBox* box) : _pset(pset), _pp(pp), _box(box) {};
	void apply();
	ParticleSet* myPset(){return _pset;};
	PairPotential* myPP(){return _pp;};
};

#endif
