#ifndef _ANDERSONTHERMOSTAT_H
#define _ANDERSONTHERMOSTAT_H

#include "Thermostat.h"

class AndersonThermostat : public Thermostat{
RealType _T,_m,_eta,_h;
public:
    AndersonThermostat(ParticleSet pset, RealType T, RealType m, RealType eta, RealType h) : Thermostat(pset), _T(T), _m(m), _eta(eta), _h(h){};
    void apply();
};

#endif
