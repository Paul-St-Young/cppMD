#include "VelocityCorrelation.h"

VelocityCorrelation::VelocityCorrelation(ParticleSet pset, int tmax)
    : Estimator(pset), _tmax(tmax) {
    _cv.reserve(tmax);
    _cvCur.reserve(tmax);
    _refVel.reserve(_pset.n);
    PosType v0(_MD_DIM,0);
    for (int i=0;i<tmax;i++){
        _cv.push_back(0);
        _cvCur.push_back(0);
        
    }
    for (int i=0;i<_pset.n;i++){
        _refVel.push_back(v0);
    }
    
    _myt=0; // myt: 0->tmax
}

void VelocityCorrelation::accumulate(int t){
    
    if (!(t%_tmax)){ // start over every tmax steps
        // dump current plot and start a new one
        for (int i=0;i<_tmax;i++){
            _cv[i] += _cvCur[i];
            _cvCur[i] = 0;
        }
        // save current velocities
        for (int i=0;i<_pset.n;i++){
            _refVel[i]=_pset.ptcls[i]->v;
        }
        _myt=0;
    }
    
    RealType T=0.0;
    //#pragma omp parallel for reduction(+:T)
    for (int i=0;i<_pset.n;i++){
        for (int coord=0;coord<_MD_DIM;coord++){
            T+=_pset.ptcls[i]->v[coord]*_refVel[i][coord];
        }
    }
    _cvCur[_myt++]=T/_pset.n;
    
}

void VelocityCorrelation::finalize(std::string filename){
    std::ofstream f;
    f.open(filename.c_str(),std::ios::out);
    for (int i=0;i<_tmax;i++){
        f << i << " " << _cv[i] << std::endl;
    }
    f.close();
}

