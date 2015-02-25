#ifndef _FORCEFIELD_H
#define _FORCEFIELD_H

#include "../Particle/ParticleSet.h"
#include "../Simulation/SimulationBox.h"
#include "PairPotential.h"
#include "Thermostat.h"

class ForceField{
ParticleSet* _pset;
PairPotential* _pp;
SimulationBox* _box;
Thermostat* _therm;
public:
	ForceField(ParticleSet* pset, PairPotential* pp, SimulationBox* box, Thermostat* therm) : _pset(pset), _pp(pp), _box(box), _therm(therm) {};
	void apply();
	ParticleSet* myPset(){return _pset;};
	PairPotential* myPP(){return _pp;};
};

#endif
