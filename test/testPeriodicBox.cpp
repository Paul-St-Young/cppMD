#include <gtest/gtest.h>
#include <cmath>
#include "../src/Particle/ParticleSet.h"
#include "../src/Simulation/PeriodicBox.h"

using namespace std;

// ----------------------- Test PutInBox ----------------------- //
TEST(BoxTest,SingleIn){
    ParticleList pool;
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    PeriodicBox box(&pset,1.0);
    box.putInBox();
    EXPECT_EQ("( 0 0 0 )",pset.ptcls[0]->str());
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,SingleXOutPos){
    ParticleList pool;
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=0.6;
    PeriodicBox box(&pset,1.0);
    box.putInBox();
    EXPECT_EQ("( -0.4 0 0 )",pset.ptcls[0]->str());
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,SingleYOutPos){
    ParticleList pool;
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[1]=0.7;
    PeriodicBox box(&pset,1.0);
    box.putInBox();
    EXPECT_EQ("( 0 -0.3 0 )",pset.ptcls[0]->str());
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,SingleZOutPos){
    ParticleList pool;
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[2]=1.7;
    PeriodicBox box(&pset,1.0);
    box.putInBox();
    EXPECT_EQ("( 0 0 -0.3 )",pset.ptcls[0]->str());
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,SingleOutNeg1){
	ParticleList pool;
	pool.push_back(new Particle);
	
    ParticleSet pset(pool);
	pset.ptcls[0]->r[0]=-0.6;
	PeriodicBox box(&pset,1.0);
	box.putInBox();
    EXPECT_EQ("( 0.4 0 0 )",pset.ptcls[0]->str());
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,SingleOutNeg2){
    ParticleList pool;
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=-0.7;
    pset.ptcls[0]->r[1]=-0.9;
    PeriodicBox box(&pset,1.0);
    box.putInBox();
    EXPECT_EQ("( 0.3 0.1 0 )",pset.ptcls[0]->str());
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

// box is defined to be [-L/2,L/2)
TEST(BoxTest,SingleBoundaryPos){
    ParticleList pool;
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=0.5;
    PeriodicBox box(&pset,1.0);
    box.putInBox();
    EXPECT_EQ("( -0.5 0 0 )",pset.ptcls[0]->str());
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,SingleBoundaryNeg){
    ParticleList pool;
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=-0.5;
    PeriodicBox box(&pset,1.0);
    box.putInBox();
    EXPECT_EQ("( -0.5 0 0 )",pset.ptcls[0]->str());
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,Double){
    ParticleList pool;
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=-0.7;
    pset.ptcls[1]->r[0]=-0.9;
    PeriodicBox box(&pset,1.0);
    box.putInBox();
    EXPECT_EQ("( 0.3 0 0 )",pset.ptcls[0]->str());
    EXPECT_EQ("( 0.1 0 0 )",pset.ptcls[1]->str());
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,Triple){
    ParticleList pool;
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=-0.7;
    pset.ptcls[1]->r[0]=-0.9;
    pset.ptcls[2]->r[0]=-0.3;
    PeriodicBox box(&pset,1.0);
    box.putInBox();
    EXPECT_EQ("( 0.3 0 0 )",pset.ptcls[0]->str());
    EXPECT_EQ("( 0.1 0 0 )",pset.ptcls[1]->str());
    EXPECT_EQ("( -0.3 0 0 )",pset.ptcls[2]->str());
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

// ----------------------- Test Displacement ----------------------- //

#define EPS 1e-5

TEST(BoxTest,InBoxDisplacementX){
    ParticleList pool;
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=0.2;
    pset.ptcls[1]->r[0]=0.3;
    PeriodicBox box(&pset,1.0);
    
    EXPECT_LE(std::abs(0.1-box.displacement(0,1)[0]),EPS);
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,ImageDisplacementX){
    ParticleList pool;
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=-0.3;
    pset.ptcls[1]->r[0]=0.3;
    PeriodicBox box(&pset,1.0);
    
    EXPECT_LE(std::abs(-0.4-box.displacement(0,1)[0]),EPS);
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,ImageDisplacementXL){
    ParticleList pool;
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=0.3;
    pset.ptcls[1]->r[0]=-0.21;
    PeriodicBox box(&pset,1.0);
    
    EXPECT_LE(std::abs(0.49-box.displacement(0,1)[0]),EPS);
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,OutBoxDisplacementX){
    ParticleList pool;
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=0.7;
    pset.ptcls[1]->r[0]=0.3;
    PeriodicBox box(&pset,1.0);
    
    EXPECT_LE(std::abs(-0.4-box.displacement(0,1)[0]),EPS);
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,OutBoxDisplacementX1){
    ParticleList pool;
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=-0.9;
    pset.ptcls[1]->r[0]=0.3;
    PeriodicBox box(&pset,1.0);
    
    EXPECT_LE(std::abs(0.2-box.displacement(0,1)[0]),EPS);
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

TEST(BoxTest,InBoxDisplacementXYZ){
    ParticleList pool;
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=0.35;
    pset.ptcls[0]->r[1]=0.1;
    pset.ptcls[0]->r[2]=-0.2;
    pset.ptcls[1]->r[0]=0.3;
    PeriodicBox box(&pset,1.0);
    
    EXPECT_LE(std::abs(-0.05-box.displacement(0,1)[0]),EPS);
    EXPECT_LE(std::abs(-0.1-box.displacement(0,1)[1]),EPS);
    EXPECT_LE(std::abs(0.2-box.displacement(0,1)[2]),EPS);
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}


TEST(BoxTest,InBoxTwoDisplacements){
    ParticleList pool;
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    pool.push_back(new Particle);
    
    ParticleSet pset(pool);
    pset.ptcls[0]->r[0]=0.35;
    pset.ptcls[1]->r[0]=0.3;
    pset.ptcls[2]->r[0]=-0.21;
    PeriodicBox box(&pset,1.0);
    
    EXPECT_LE(std::abs(-0.05-box.displacement(0,1)[0]),EPS);
    EXPECT_LE(std::abs(0.44-box.displacement(0,2)[0]),EPS);
    EXPECT_LE(std::abs(0.49-box.displacement(1,2)[0]),EPS);
    
    for (int i=0;i<pool.size();i++){
        delete pool[i];
    }
}

// ======================= Test Main ======================= //
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
