#include "Nose-Hoover.h"

NoseHooverThermostat::NoseHooverThermostat(ParticleSet pset, RealType T, RealType Q, RealType b, RealType h, int nequil, bool keep) : Thermostat(pset,nequil,keep), _T(T), _Q(Q), _b(b), _h(h) {
    _beta=1/T;
    _g=3*_pset.n+1;
}

void NoseHooverThermostat::apply(){
    for (int i=0;i<_pset.n;i++){
        for (int coord=0;coord<_MD_DIM;coord++)
        _pset.ptcls[i]->a[coord] -= _b*_pset.ptcls[i]->v[coord];
    }
    RealType halfK=0;
    for (int i=0;i<_pset.n;i++){
        for (int coord=0;coord<_MD_DIM;coord++){
            halfK += _pset.ptcls[i]->m*(_pset.ptcls[i]->v[coord],2);
        }
    }
    _b += 1/_Q*(halfK-_g/_beta)*_h;
}

