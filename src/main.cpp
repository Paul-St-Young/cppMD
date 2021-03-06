#include <fstream>

#include "Interface/TypeFactory.h"
#include "Interface/InputManager.h"
#include "Particle/ParticleSet.h"
#include "Particle/ParticlePool.h"
#include "Simulation/PeriodicBox.h"
#include "ForceField/Lennard-Jones.h"
#include "ForceField/ForceField.h"
#include "Updator/AndersonThermostat.h"
#include "Updator/Nose-Hoover.h"
#include "Updator/VelocityVerlet.h"
#include "Updator/Metropolis.h"
#include "Estimator/KineticEnergyEstimator.h"
#include "Estimator/PotentialEstimator.h"
#include "Estimator/MomentumEstimator.h"
#include "Estimator/PairCorrelationEstimator.h"
#include "Estimator/StructureFactorEstimator.h"
#include "Estimator/VelocityCorrelation.h"
#include "Estimator/VacancyEstimator.h"

using namespace std;

int main(int argc, char* argv[]){

    if (argc<2){
        cout << "please specify input" << endl;
        exit(0);
    }

    // initialize parameters
    RealType sigma,epsilon,eta,b,Q,msigma,dt;
    bool useForce;
    InputManager manager(argv[1]);
    
    int nequil=atoi(manager["simulation"]["nequil"].c_str());
    int nsteps=atoi(manager["simulation"]["nsteps"].c_str());
    RealType h=atof(manager["simulation"]["stepsize"].c_str());
    RealType T=atof(manager["simulation"]["temperature"].c_str());
    
    int n=atoi(manager["particles"]["n"].c_str());
    RealType m=atoi(manager["particles"]["mass"].c_str());
    int nRemove=atoi(manager["particles"]["remove"].c_str());
    
    string boxType=manager["box"]["type"];
    RealType L=atof(manager["box"]["size"].c_str());
    
    string pairPotentialType=manager["forcefield"]["pairpotential"];
    if (pairPotentialType=="Lennard-Jones"){
        sigma=atof(manager["forcefield"]["sigma"].c_str());
        epsilon=atof(manager["forcefield"]["epsilon"].c_str());
    }
    
    string updatorType=manager["updator"]["type"];
    if (updatorType=="Metropolis"){
        msigma=atof(manager["updator"]["sigma"].c_str());
        useForce=(manager["updator"]["force"]=="yes");
        dt=atof(manager["updator"]["dt"].c_str());
    }
    
    string thermostatType=manager["thermostat"]["type"];
    bool keep=( manager["thermostat"]["keep"]=="yes" );
    if (thermostatType=="Anderson"){
        // collision coupling strength eta*h shoud be around 0.01 (1%)
        eta=atof(manager["thermostat"]["eta"].c_str());
    } else if (thermostatType=="Nose-Hoover") {
        b=atof(manager["thermostat"]["b"].c_str());
        Q=atof(manager["thermostat"]["Q"].c_str());
    }
    
    RealType rmin=atof(manager["estimator"]["rmin"].c_str()); // PairCorrelationEstimator
    RealType rmax=atof(manager["estimator"]["rmax"].c_str());
    RealType dr=atof(manager["estimator"]["dr"].c_str());
    
    int maxK=atoi(manager["estimator"]["maxK"].c_str()); // StructureFactorEstimator 
    int tmax=atof(manager["estimator"]["tmax"].c_str()); // VelocityCorrelation
    string traj=manager["output"]["trajectory"]; // Output files
    string vacTraj=manager["particles"]["vacFile"];
    
    // generate particles
    ParticlePool globalPool(n); // memory allocated here
    globalPool.setMasses(m);
    globalPool.initCubicPositions(L);
    globalPool.initVelocities(T,m);
    
    // put in global particle set
    ParticleSet gPset(globalPool.myParticles());
    if (nRemove!=0) gPset.removeParticle(nRemove);

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
    if (thermostatType=="Anderson") 
        therm = new AndersonThermostat(gPset,T,m,eta,h,nequil,keep);
    else if (thermostatType=="Nose-Hoover") 
        therm = new NoseHooverThermostat(gPset,T,Q,b,h,nequil,keep);
    else therm = new Thermostat(gPset); // no thermostat
    
    Updator* updator;
    if (updatorType=="Verlet"){
        updator = new VelocityVerlet(&gPset,ff,box,therm);
        updator->h=h;
    }
    else if (updatorType=="Metropolis")
        updator = new Metropolis(&gPset,ff,box,therm,msigma,T,useForce,dt);
    else updator = new Updator(&gPset,ff,box,therm); // no updator

    // throw in some estimators
    Estimator *kinetic, *potential, *momentum, *pairCorr, *sk, *cv, *vac;
    kinetic     = new KineticEnergyEstimator(gPset);
    potential   = new PotentialEstimator(gPset,pp,box);
    momentum    = new MomentumEstimator(gPset);
    pairCorr    = new PairCorrelationEstimator(gPset,box,rmax,dr,L);
    sk          = new StructureFactorEstimator(gPset,L,maxK);
    cv          = new VelocityCorrelation(gPset,tmax);
    vac         = new VacancyEstimator(gPset,64,box,vacTraj);

    RealType K,U,Ti; // Kinetic, Potential, Temperature (instantaneous)
    PosType  P(_MD_DIM,0.0), Gr((int)rmax/dr,0.0); // Momentum, Pair Correlation
    
    // perform MD simulation
    for (int step=0; step < nequil; step++) updator->update(); // equilibrate 
    gPset.clearFile(traj);
    for (int step=0; step < nsteps; step++){ // run
        // Estimators
        U=potential->scalarEvaluate();
        /*K=kinetic->scalarEvaluate();
        P=momentum->vectorEvaluate();*/
        pairCorr->appendFile("gr.dat",step);
        sk->accumulate(step);
        PosType vec; vec.reserve(_MD_DIM);
        vec = vac->vectorEvaluate();
        for (int coord=0;coord<_MD_DIM;coord++)
            cout << vec[coord] << " ";
        cout << endl;
        /*
        cv->accumulate(step);
        Ti=2.*K/3./n;
        cout << step << " ("<< U << " " << K << " " << Ti << " " << K+U << ")" << endl;
        */
        //cout << step << " ("<<U<<") " << endl;
        updator->update();
        
        gPset.appendFile(traj);
    }
    sk->finalize("sk.dat");
    //cv->finalize("cv.dat");
    cerr << "Acceptance Ratio: " << updator->acceptedSteps()/(RealType)((nsteps+nequil)*n) << endl;
	
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
