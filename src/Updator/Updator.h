#ifndef _UPDATOR_H
#define _UPDATOR_H
#include <iostream>
#include "../Particle/ParticleSet.h"
#include "../ForceField/ForceField.h"
#include "../Simulation/SimulationBox.h"
#include "Thermostat.h"
class Updator{
protected:
	ParticleSet* _pset;
	ForceField* _ff;
	SimulationBox* _box;
	Thermostat* _therm;
public:
	Updator(ParticleSet* pset, ForceField* ff, SimulationBox* box, Thermostat* therm) : _pset(pset), _ff(ff), _box(box), _therm(therm)
		{Rcut=0.0;h=0.0;}; // do not apply forces by default
    virtual void update(){
        std::cerr << "Updator::update being called" << std::endl;
    };
	RealType Rcut,h;
};

#endif
