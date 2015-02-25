#include "Nose-Hoover.h"

NoseHooverThermostat::NoseHooverThermostat(ParticleSet pset, RealType T, RealType m, RealType Q) : Thermostat(pset), _T(T), _m(m), _Q(Q) {
    RealType _beta=1/T;
    int g=3*_pset.n+1;
}

void NoseHooverThermostat::apply(){
    _b=1.0;
    for (int i=0;i<_pset.n;i++){
        for (int coord=0;coord<_MD_DIM;coord++)
        _pset.ptcls[i]->a[coord]-=_b*_pset.ptcls[i]->v[coord];
    }
}

