#include "VelocityVerlet.h"

void VelocityVerlet::update(){
	
	_ff->apply();  // fill the acceleration in particle set
	// update positions and store acceleration
	for (int i=0;i<_pset->n;i++){
		for (int coord=0;coord<_MD_DIM;coord++){
			_oldA[i][coord]=(_pset->ptcls[i]->a[coord]);
		}
		for (int coord=0;coord<_MD_DIM;coord++){
			_pset->ptcls[i]->r[coord] += _pset->ptcls[i]->v[coord]*h+0.5*_oldA[i][coord]*h*h;
		}
	}
	// put everyone in box
	_box->putInBox();
	
	_ff->apply(); // get force at new positions
	// update velocities
	for (int i=0;i<_pset->n;i++){
		for (int coord=0;coord<_MD_DIM;coord++){
			_pset->ptcls[i]->v[coord] += 0.5*(_oldA[i][coord]+_pset->ptcls[i]->a[coord])*h;
		}
	}
	
}

VelocityVerlet::~VelocityVerlet(){

    for (int i=0;i<_pset->n;i++){
        _oldA[i].clear();
        _oldA[i].resize(0);
    }
    _oldA.clear();
    _oldA.resize(0);

}
