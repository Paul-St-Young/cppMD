Getting Started
====
To build
----
  mkdir build
  cd build
  cmake ..
  make
To run
----
  ./cppMD

Class Structure
====

Main
====

1. Generate a pool of particles (taking up significant physical memory)
2. Create a light-weighed ParticleSet to partition the particles
3. Create a SimulationBox to manipulate the partition
4. A ForceField is created with a PairPotential
5. An Updator is created to tie together [ParticleSet,ForceField,SimulationBox]
6. Perform MD simulation and report statistics

Particle
====
The most basic objects to be manipulated

ClassicalParticles
----

QuantumParticles
----

ParticleSet
====

Box
====
A container for particle sets, used to impose boundary conditions. The box is also responsible for maintaining a distance tables for the global particle set

PeriodicBox
----
Knows where to put particles when they go out of bounds, knows the shortest distances between particles.

Updator
====
The most complicated class in this program, used to drive the particles around. An updator should always have a pair potential generator, a thermostat and an update method to manimulate a particle set.

Velocity Verlet
----


PairPotential
====
Given a particle and a particle set, the pair potential object should be able to determine the force on the given particle

LJ
----
Lennard-Jones pair potential
	
Thermostat
====

AndersonThermostat
----
