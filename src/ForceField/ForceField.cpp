#include "ForceField.h"

void ForceField::apply(){

	// zero out acceleration
	for (int i=0;i<_pset->n;i++){
		for (int coord=0;coord<_MD_DIM;coord++){
			_pset->ptcls[i]->a[coord]=0;
		}
	}
	
	// calculate new acceleration
	PosType grad(_MD_DIM,0.0); // temporary variable for potential gradient
	PosType dR(_MD_DIM,0.0);   // temporary variable for displacement vector
	#pragma omp parallel for private(dR) private(grad) schedule(static,1)
	for (int i=0;i<_pset->n;i++){
	    for (int j=0;j<_pset->n;j++){
	        if (i!=j){
	            dR=_box->displacement(i,j);
	            grad=_pp->gradient(dR);
	            for (int coord=0;coord<_MD_DIM;coord++){
	                _pset->ptcls[i]->a[coord]+=grad[coord]/_pset->ptcls[i]->m;
	            }
	        }
	    }
	}

}

void ForceField::apply(int i){

    // zero out acceleration
    for (int coord=0;coord<_MD_DIM;coord++)
        _pset->ptcls[i]->a[coord]=0;
    
    PosType dR(_MD_DIM,0.0);
    PosType grad(_MD_DIM,0.0);
    for (int j=0;j<_pset->n;j++){
        if (i!=j){
            dR=_box->displacement(i,j);
            grad=_pp->gradient(dR);
            for (int coord=0;coord<_MD_DIM;coord++){
                _pset->ptcls[i]->a[coord]+=grad[coord]/_pset->ptcls[i]->m;
            }
        }
    }
}
