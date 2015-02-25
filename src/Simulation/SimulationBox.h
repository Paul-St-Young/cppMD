#ifndef _SIMULATION_BOX
#define _SIMULATION_BOX

#include <iostream>

#include "../Particle/Particle.h"
#include "../Particle/ParticleSet.h"

class SimulationBox{
protected:
    ParticleSet* _pset;
public:
    SimulationBox(){};
    ~SimulationBox(){};
    SimulationBox(ParticleSet* pset) : _pset(pset){};
    virtual void putInBox(){};
    virtual PosType displacement(int i, int j){
    std::cerr << "SimulationBox::displacement being called" << std::endl;
    }; // return the vector ptcl[i]->ptcl[j]
	virtual RealType distance(int i, int j){}; // return the magnitue of displacement
};

#endif 
