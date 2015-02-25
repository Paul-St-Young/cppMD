#ifndef _PERIODIC_BOX
#define _PERIODIC_BOX

#include "SimulationBox.h"

class PeriodicBox: public SimulationBox {
RealType _L;
public:
    PeriodicBox(ParticleSet* pset,RealType L) : SimulationBox(pset),_L(L){};
    void putInBox();
	PosType displacement(int i, int j); // return the vector ptcl[i]->ptcl[j]
	RealType distance(int i, int j); // return the magnitue of displacement
	RealType size(){return _L;};
};

#endif 
