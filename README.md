Getting Started
---------------

### To build
    mkdir build
    cd build
    cmake ..
    make

### to run
    ./cppDFT 

### requirement
1. cmake 2.8.8 or above
2. c++11 compatible compiler

Class Structure
---------------

### Particle Management
* Particle
* ParticlePool
* ParticleSet

A particle is basically a collection of attributes such as posiotion, velocity, acceleration, mass and charge. A ParticlePool contains physical particles and is responsible for their memory allocation, deallocation and initialization. A ParticleSet maintains a list of pointers to the particles of interest.
  
  The idea is to have a "heavy" object ParticlePool that manages memory allocation and then have mutiple "light" objects ParticleSet to manipulate the data. A typical starting point is
  
    ParticlePool pPool(8); 
    pPool.initCubicPositions(1.0);
    ParticleSet gPset(pPool.myParticles());
  
  which:
  1. initialize 3 particles at the origin
  2. call an initialization method to redistribute the particles - most simulations don't allow two particles at the same position
  3. allow a particle set to control some particles in the pool (partial pool control is not yet implemented, so all particle sets are global particle sets at the moment)

Main
====

1. Generate a pool of particles (taking up significant physical memory)
2. Create a light-weighed ParticleSet to partition the particles
3. Create a SimulationBox to manipulate the partition
4. A ForceField is created with a PairPotential
5. An Updator is created to tie together [ParticleSet,ForceField,SimulationBox]
6. Perform MD simulation and report statistics

### Box
A container for particle sets, used to impose boundary conditions. The box is also responsible for maintaining a distance tables for the global particle set

#### PeriodicBox
Knows where to put particles when they go out of bounds, knows the shortest distances between particles.

### Updator
An updator should have a pair potential generator, a thermostat and an update method to manimulate a particle set.

#### Velocity Verlet

#### Thermostat

##### AndersonThermostat

##### Nose-Hoover

### ForceField
#### PairPotential
Given a particle and a particle set, the pair potential object should be able to determine the force on the given particle

##### LJ
Lennard-Jones pair potential
	

