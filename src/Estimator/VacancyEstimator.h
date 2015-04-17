#ifndef _VACANCYESTIMATOR_H
#define _VACANCYESTIMATOR_H

#include "Estimator.h"
#include "../Simulation/SimulationBox.h"

class VacancyEstimator : public Estimator{
ParticlePool* _latticeParticles;
ParticleSet* _lattice;
SimulationBox* _box;
int _nlattice; // better be a perfect cubic
std::string _vacTraj; // vacancy trajectory file
public:
    VacancyEstimator(ParticleSet pset,int nlattice, SimulationBox* box, std::string vacTraj);
    ~VacancyEstimator();
	PosType vectorEvaluate();
};

#endif
