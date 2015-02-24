#ifndef _PARTICLE_CPP
#define _PARTICLE_CPP

#include "Particle.h"
#include <sstream>

Particle::Particle(){
    name="";
	m=0.0;
	for (int i=0;i<_MD_DIM;i++){
		r.push_back(0.0);
		v.push_back(0.0);
		a.push_back(0.0);
	}
};

std::ostream& operator<<(std::ostream& os, const Particle& ptcl){
    os << "( ";
    for (PosType::const_iterator it=ptcl.r.begin();it!=ptcl.r.end();it++){
    os << *it << " ";
    } os << ")";
    return os;
}

std::string Particle::str(){
    std::ostringstream os;
    os << "( ";
    for (PosType::const_iterator it=r.begin();it!=r.end();it++){
    os << *it << " ";
    } os << ")";
    return os.str();
}

#endif
