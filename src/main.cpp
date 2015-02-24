#include <fstream>

#include "Interface/TypeFactory.h"
#include "Particle/ParticleSet.h"
#include "Particle/ParticlePool.h"
#include "Simulation/PeriodicBox.h"
#include "ForceField/Lennard-Jones.h"
#include "ForceField/ForceField.h"
#include "Updator/VelocityVerlet.h"
#include "Estimator/KineticEnergyEstimator.h"
#include "Estimator/PotentialEstimator.h"

using namespace std;

int main(int argc, char* argv[]){

    int n=64; // simulating 64 particles
    RealType L=4.2323167; // size of simulation box
    RealType m=48.0; // mass of the particles
    int nsteps=1000; // simulation steps
    RealType h=0.01; // simulation step size
    RealType sigma=1.0, epsilon=1.0; // Lennard-Jones parameters

    // generate particles
    ParticlePool globalPool(n);
    globalPool.readPositions ("../R.txt");
    globalPool.readVelocities("../V.txt");
    globalPool.setMasses(m);
	
    // put in global particle set
    ParticleSet gPset(globalPool.myParticles());
	
    // tell box to manage pset
    SimulationBox* box;
    box=new PeriodicBox(&gPset,L);
    box->putInBox();
    
    // build a force field with a pair potential and a thermostat (later)
	PairPotential* pp;
	pp = new LennardJones(sigma,epsilon);
    ForceField* ff;
	ff = new ForceField(&gPset,pp,box);
	
	// tell the updator to update particle set with the force field inside the box
    Updator* updator;
    updator = new VelocityVerlet(&gPset,ff,box); 
	updator->h=h;
	
	// throw in some estimators
    Estimator *kinetic, *potential;
    kinetic = new KineticEnergyEstimator(gPset);
    potential = new PotentialEstimator(gPset,pp,box);
	
	/* report generation
	ff->apply();
	cout << "Initalized:" << endl;
	for (int i=0;i<gPset.n;i++){
		cout << "  Particle " << i << " position" << gPset.ptcls[i]->str() << endl;
		cout << "             " << " velocity " << str( gPset.ptcls[i]->v ) << endl;
	    for (int coord=0;coord<_MD_DIM;coord++) gPset.ptcls[i]->a[coord]*=m;
		cout << "             " << " force " << str(gPset.ptcls[i]->a) << endl;
	}*/
	
	// clear trajectory file
	ofstream fs;
	fs.open("myTrajectory.xyz",ios::out);
	fs.close();
	
	RealType T,U;
    // perform MD simulation
    for (int step=0; step < nsteps; step++){
        U=potential->scalarEvaluate();
        T=kinetic->scalarEvaluate();
        cout << step << " ("<< U << " " << T << " " << T+U << ")" << endl;
        updator->update();
        gPset.appendFile("myTrajectory.xyz");
    }
	
	delete kinetic;
	delete potential;
	delete box;
	delete pp;
	delete ff;
	delete updator;

return 0;
}
