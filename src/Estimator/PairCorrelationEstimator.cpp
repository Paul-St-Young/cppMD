#include "PairCorrelationEstimator.h"

#include <cmath>

void PairCorrelationEstimator::appendFile(std::string filename,int t){
    int n=(int)(_rmax-_rmin)/_dr; // number of grid points for histogram
    
    PosType gr(n,0.0);
    RealType r;
    
    // histogram the inter-particle distance
    for (int i=0;i<_pset.n;i++){
	    for (int j=i+1;j<_pset.n;j++){
	        r=_box->distance(i,j);
            if (r>_rmin && r<_rmax)
	            gr[(int)(r/_dr)]+=1;
	    }
    }
    
    // normalize g(r)
    for (int i=1;i<gr.size();i++){
        gr[i]/=4*M_PI*std::pow(i*_dr,2)*_dr
            *((RealType)_pset.n/std::pow(_L,3));
    }
    
    // appendFile
    std::ofstream fs;
    fs.open(filename.c_str(),std::ios::app);
    fs << t << " " << str(gr) << std::endl;
    fs.close();
}
