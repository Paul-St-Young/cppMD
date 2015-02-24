#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <iostream>
#include <vector>

#include "../Interface/TypeFactory.h"



class Particle{

public:
    std::string name;
    PosType r,v,a; // position, velocity, acceleration
    RealType m; // mass
    Particle(); // empty constructor
    ~Particle(){};
    std::string str();
};

std::ostream& operator<<(std::ostream& os, const Particle& ptcl);



#endif
