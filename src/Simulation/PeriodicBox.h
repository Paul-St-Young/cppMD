#ifndef _PERIODIC_BOX
#define _PERIODIC_BOX

#include "SimulationBox.h"

class PeriodicBox: public SimulationBox {
public:
    PeriodicBox(ParticleSet* pset,RealType L) : SimulationBox(pset,L){};
    void putInBox();
	PosType displacement(int i, int j); // return the vector ptcl[i]->ptcl[j]
	PosType displacement(PosType v1, PosType v2);
	RealType distance(int i, int j); // return the magnitue of displacement
	RealType distance(PosType v1, PosType v2);
	RealType size(){return _L;};
};

#endif 
