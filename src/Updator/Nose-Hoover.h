#ifndef _NOSEHOOVERTHERMOSTAT_H
#define _NOSEHOOVERTHERMOSTAT_H

#include "Thermostat.h"

class NoseHooverThermostat : public Thermostat{
RealType _T,_m,_Q,_beta,_g;
RealType _b;
public:
    NoseHooverThermostat(ParticleSet pset, RealType T, RealType m, RealType Q,RealType b, int nequil=0, bool keep=true);
    void apply();
};

#endif
