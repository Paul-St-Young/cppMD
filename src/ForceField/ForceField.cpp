#include "ForceField.h"

void ForceField::apply(){

	// zero out acceleration
	for (int i=0;i<_pset->n;i++){
		for (int coord=0;coord<_MD_DIM;coord++){
			_pset->ptcls[i]->a[coord]=0;
		}
	}
	
	PosType grad(_MD_DIM,0.0); // temporary variable for potential gradient
	// calculate new acceleration
	
	for (int i=0;i<_pset->n;i++){
	    for (int j=0;j<_pset->n;j++){
	        if (i!=j){
	            grad=_pp->gradient(_box->displacement(i,j));
	            for (int coord=0;coord<_MD_DIM;coord++){
	                _pset->ptcls[i]->a[coord]+=grad[coord]/_pset->ptcls[i]->m;
	            }
	        }
	    }
	}
	
}

