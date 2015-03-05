#include "StructureFactorEstimator.h"

#include <iostream>
#include <fstream>

using namespace std;

StructureFactorEstimator::StructureFactorEstimator(ParticleSet pset, RealType L, int maxK) 
    : Estimator(pset), _L(L), _maxK(maxK){
    kVecs=_leagalKVecs(_maxK); 
    std::vector<ComplexType> SK0(kVecs.size(),0.0);
    SK.swap(SK0);
    _mystep=0;
}

ComplexType StructureFactorEstimator::_rhoK(PosType k){

    ComplexType rho(0,0);
    ComplexType I(0,1);
    for (int i=0;i<_pset.n;i++){
        RealType dot=0;
        for (int coord=0;coord<_MD_DIM;coord++){
            dot+=_pset.ptcls[i]->r[coord]*k[coord];
        }
        rho+=std::exp(I*dot);
    }
    return rho;
}

std::vector<PosType> StructureFactorEstimator::_leagalKVecs(int maxK){
    std::vector<PosType> kVecs;
    for (int nx=0;nx<maxK;nx++){
        for (int ny=0;ny<maxK;ny++){
            for (int nz=0;nz<maxK;nz++){
                PosType k {2*(RealType)M_PI/_L*nx,2*(RealType)M_PI/_L*ny,2*(RealType)M_PI/_L*nz};
                kVecs.push_back(k);
            }
        }
    }
    return kVecs;
}


void StructureFactorEstimator::accumulate(int t){
    #pragma omp parallel for schedule(static,1)
    for (int i=0;i<kVecs.size();i++){
        PosType nkVec(kVecs[i]);
        for (int coord=0;coord<_MD_DIM;coord++){
            nkVec[coord]*=-1;
        }
        SK[i]+=_rhoK(kVecs[i])*_rhoK(nkVec)/(RealType)_pset.n;
        _mystep++;
    }
}

void StructureFactorEstimator::finalize(std::string filename){
    std::ofstream skFile;
    skFile.open(filename.c_str(),std::ios::out);
    for (int i=0;i<kVecs.size();i++){
        RealType kMag=0.0;
        for (int coord=0;coord<_MD_DIM;coord++){
            kMag += std::sqrt(kVecs[i][coord]*kVecs[i][coord]);
        }
        skFile << kMag << " " << SK[i]/(RealType)_mystep << std::endl;
    }
    skFile.close();
};
