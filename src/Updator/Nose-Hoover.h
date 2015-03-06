#ifndef _NOSEHOOVERTHERMOSTAT_H
#define _NOSEHOOVERTHERMOSTAT_H

#include "Thermostat.h"

class NoseHooverThermostat : public Thermostat{
RealType _T,_Q,_beta,_b,_h;
int _g;
public:
    NoseHooverThermostat(ParticleSet pset, RealType T, RealType Q,RealType b,RealType h, int nequil=0, bool keep=true);
    void apply();
};

#endif
