#ifndef _THERMOSTAT_H
#define _THERMOSTAT_H

#include "../Particle/ParticleSet.h"

class Thermostat{
protected:
    ParticleSet _pset;
    int _nequil,_mystep;
    bool _keep; // keep thermostat after equilibration?
public:
    Thermostat(ParticleSet pset, int nequil=0, bool keep=true) : _pset(pset), _nequil(nequil), _keep(keep) {_mystep=0;};
    virtual void apply(){};
};

#endif
