#ifndef _SIMULATION_BOX
#define _SIMULATION_BOX

#include <iostream>

#include "../Particle/Particle.h"
#include "../Particle/ParticleSet.h"

class SimulationBox{
protected:
    ParticleSet* _pset;
    RealType _L;
public:
    SimulationBox(){};
    ~SimulationBox(){};
    SimulationBox(ParticleSet* pset, RealType L) : _pset(pset), _L(L) {};
    RealType L(){return _L;};
    virtual void putInBox(){};
    virtual PosType displacement(int i, int j){}; // return the vector ptcl[i]->ptcl[j]
    virtual PosType displacement(PosType v1, PosType v2){};
	virtual RealType distance(int i, int j){}; // return the magnitue of displacement
	virtual RealType distance(PosType v1, PosType v2){};
};

#endif 
