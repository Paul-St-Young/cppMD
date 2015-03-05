#include <fstream>

#include "Interface/TypeFactory.h"
#include "Particle/ParticleSet.h"
#include "Particle/ParticlePool.h"
#include "Simulation/PeriodicBox.h"
#include "ForceField/Lennard-Jones.h"
#include "Updator/AndersonThermostat.h"
#include "Updator/Nose-Hoover.h"
#include "ForceField/ForceField.h"
#include "Updator/VelocityVerlet.h"
#include "Estimator/KineticEnergyEstimator.h"
#include "Estimator/PotentialEstimator.h"
#include "Estimator/MomentumEstimator.h"
#include "Estimator/PairCorrelationEstimator.h"
#include "Estimator/StructureFactorEstimator.h"
#include "Estimator/VelocityCorrelation.h"

using namespace std;

int main(int argc, char* argv[]){

    RealType T=0.728; // temperature
    T=atof(argv[1]);

    int n=64; // simulating 64 particles
    
    RealType L=4.2323167; // size of simulation box
    RealType m=48.0; // mass of the particles
    int nsteps=1000; // simulation steps
    RealType h=0.01; // simulation step size
    RealType sigma=1.0, epsilon=1.0; // Lennard-Jones parameters
    
    // AndersonThermostat
    RealType eta=1.0; // collision coupling strength eta*h shoud be around 0.01 (1%)
    
    // NoseHooverThermostat
    RealType b=0.0; // drag coefficient
    RealType Q=1.0; // coupling strength
    
    //PairCorrelationEstimator
    RealType rmax=4.0;
    RealType dr=0.1;
    
    // StructureFactorEstimator
    int maxK=5;
    
    // VelocityCorrelation
    int tmax=100;
    
    // generate particles
    ParticlePool globalPool(n); // memory allocated here
    globalPool.setMasses(m);
    globalPool.initCubicPositions(L);
    globalPool.initVelocities(T,m);
    
    // put in global particle set
    ParticleSet gPset(globalPool.myParticles());

    // tell box to manage pset
    SimulationBox* box;
    box=new PeriodicBox(&gPset,L);
    box->putInBox();

    // build a force field with a pair potential
    PairPotential* pp;
    pp = new LennardJones(sigma,epsilon);
    ForceField* ff;
    ff = new ForceField(&gPset,pp,box);

    // tell the updator to update particle set with the force field inside the box 
      //  and give it a thermostat to control temperature
    Thermostat* therm;
    therm = new Thermostat(gPset);
    //therm = new AndersonThermostat(gPset,T,m,eta,h);
    //therm = new NoseHooverThermostat(gPset,T,m,Q,b);
    
    Updator* updator;
    updator = new VelocityVerlet(&gPset,ff,box,therm); 
    updator->h=h;

    // throw in some estimators
    Estimator *kinetic, *potential, *momentum, *pairCorr, *sk, *cv;
    kinetic     = new KineticEnergyEstimator(gPset);
    potential   = new PotentialEstimator(gPset,pp,box);
    momentum    = new MomentumEstimator(gPset);
    pairCorr    = new PairCorrelationEstimator(gPset,box,rmax,dr,L);
    sk          = new StructureFactorEstimator(gPset,L,maxK);
    cv          = new VelocityCorrelation(gPset,tmax);
    
    // clear trajectory file
    ofstream fs;
    fs.open("myTrajectory.xyz",ios::out);
    fs.close();

    RealType K,U,Ti; // Kinetic, Potential, Temperature (instantaneous)
    PosType  P(_MD_DIM,0.0), Gr((int)rmax/dr,0.0); // Momentum, Pair Correlation
    
    // perform MD simulation
    for (int step=0; step < nsteps; step++){
        // Estimators
        U=potential->scalarEvaluate();
        K=kinetic->scalarEvaluate();
        P=momentum->vectorEvaluate();
        pairCorr->appendFile("gr.dat",step);
        sk->accumulate(step);
        cv->accumulate(step);
        Ti=2.*K/3./n;
        
        cout << step << " ("<< U << " " << K << " " << Ti << " " << K+U << ")" << endl;
        updator->update();
        
        gPset.appendFile("myTrajectory.xyz");
    }
    sk->finalize("sk.dat");
    cv->finalize("cv.dat");
    
	
	delete kinetic;
	delete potential;
	delete momentum;
	delete pairCorr;
	delete sk;
	delete cv;
	
	delete box;
	delete pp;
	delete ff;
	delete therm;
	delete updator;

return 0;
}
