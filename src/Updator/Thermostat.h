#ifndef _THERMOSTAT_H
#define _THERMOSTAT_H

#include "../Particle/ParticleSet.h"

class Thermostat{
protected:
    ParticleSet _pset;
public:
    Thermostat(ParticleSet pset) : _pset(pset){};
    virtual void apply(){};
};

#endif
