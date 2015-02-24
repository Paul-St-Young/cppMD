#include "PotentialEstimator.h"

RealType PotentialEstimator::scalarEvaluate(){
    RealType U=0.0;
    PosType  dR(3,0.0);
    //#pragma omp parallel for reduction(+:U) private(dR) schedule(static,1)
    for (int i=0;i<_pset.n;i++){
	    for (int j=i+1;j<_pset.n;j++){
	    
	        dR=_box->displacement(i,j);
	        U+=_pp->potential(dR);
	    }
    }
    return U;
}
