#include "StructureFactorEstimator.h"

std::complex<RealType> StructureFactorEstimator::_rhoK(PosType k){

    std::complex<RealType> rho(0,0);
    for (int i=0;i<_pset.n;i++){
        RealType dot=0;
        for (int coord=0;coord<_MD_DIM;coord++){
            dot+=_pset.ptcls[i]->r[coord]*k[coord];
        }
        rho+=std::exp(i*dot);
    }

    return rho;
}

std::vector<PosType> StructureFactorEstimator::_leagalKVects(int maxK){
    std::vector<PosType> kVecs;
    for (int nx=0;nx<maxK;nx++){
        for (int ny=0;ny<maxK;ny++){
            for (int nz=0;nz<maxK;nz++){
                PosType k {(RealType)M_PI/_L*nx,(RealType)M_PI/_L*ny,(RealType)M_PI/_L*nz};
                kVecs.push_back(k);
            }
        }
    }
    return kVecs;
}


RealType StructureFactorEstimator::scalarEvaluate(){
    std::complex<RealType> Sk(0,0);
    
    std::vector<PosType> kVecs=_leagalKVects(_maxK);    
    for (int i=0;i<kVecs.size();i++){
        Sk+=_rhoK(kVecs[i]);
    }
    //return Sk;
}
