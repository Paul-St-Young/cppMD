#include "MomentumEstimator.h"

PosType MomentumEstimator::vectorEvaluate(){
    PosType P(_MD_DIM,0.0);
    //#pragma omp parallel for reduction(+:P)
    for (int i=0;i<_pset.n;i++){
        for (int coord=0;coord<_MD_DIM;coord++){
            P[coord]+=_pset.ptcls[i]->m 
                * _pset.ptcls[i]->v[coord];
        }
    }

    return P;
}
