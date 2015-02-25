#ifndef _VELOCITYVERLET_H
#define _VELOCITYVERLET_H

#include "Updator.h"

class VelocityVerlet: public Updator {
std::vector<PosType> _oldA; // need to store old acceleration
public:
	VelocityVerlet(ParticleSet* pset, ForceField* ff,SimulationBox* box):Updator(pset,ff,box){
		// !!!! There's a memory leak here ? !!!!
		for (int i=0;i<_pset->n;i++){
			PosType a(_MD_DIM,0.0);
			_oldA.push_back(a);
		}
	};
    void update();
};

#endif
