#include "PeriodicBox.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

void PeriodicBox::putInBox(){

    for (int i=0;i<_pset->n;i++){
		for (int coord=0;coord<_MD_DIM;coord++){
			if (_pset->ptcls[i]->r[coord] < -_L/2. || _pset->ptcls[i]->r[coord] >= _L/2. ){
				RealType mod = fmod(_pset->ptcls[i]->r[coord]+_L/2.,_L);
				if (mod >=0){
					_pset->ptcls[i]->r[coord]= mod - _L/2.;
				} else {
					_pset->ptcls[i]->r[coord]= mod + _L/2.;
				}
			}
		}
	}
	
}

PosType PeriodicBox::displacement(int i, int j){
    PosType dR(_MD_DIM,0.0);
    
    // assume everyone's in box already
    
    // assess each coordinate
    for (int coord=0;coord<_MD_DIM;coord++){
        int min=0; // assume left image is cloest
        // assess 3 images
        RealType dLeft =_pset->ptcls[j]->r[coord]-_pset->ptcls[i]->r[coord]-_L;
        RealType dHere =_pset->ptcls[j]->r[coord]-_pset->ptcls[i]->r[coord];
        if (std::abs(dHere)<std::abs(dLeft)) min=1;
        RealType dRight=_pset->ptcls[j]->r[coord]-_pset->ptcls[i]->r[coord]+_L;
        if (std::abs(dRight)<std::abs(dLeft) && std::abs(dRight)<std::abs(dHere)) min=2;
        
        // assign minimum image
        if (min==0) dR[coord]=dLeft;
        else if (min==1) dR[coord]=dHere;
        else if (min==2) dR[coord]=dRight;
        else{
            std::cerr << "Minimum Image Error" << std::endl;
            std::exit(1);
        }
        
    }
    
    return dR;
}

RealType PeriodicBox::distance(int i, int j){
    RealType d2=0.0;
    PosType dR=displacement(i,j);
    for (int i=0;i<_MD_DIM;i++) d2+=dR[i]*dR[i];
    return std::sqrt(d2);
}
