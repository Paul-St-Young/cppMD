#include "ParticleSet.h"

#include <iostream>
#include <fstream>

void ParticleSet::appendFile(std::string filename){
    std::ofstream fs;
    fs.open(filename.c_str(),std::ios::app);
    if (fs.is_open()){
        fs << std::endl << n << std::endl;
        for (int i=0;i<n;i++){
            fs << i;
            for (int coord=0;coord<_MD_DIM;coord++){
                fs << " " << ptcls[i]->r[coord];
            } fs << std::endl;
        }
    }
    fs.close();
}

void ParticleSet::removeParticle(int i){
    for (int j=i;j<n-1;j++){
        ptcls[j]=ptcls[j+1];
    }
    n-=1;
}

void ParticleSet::clearFile(std::string filename){
    std::ifstream fs;
    fs.open(filename.c_str(),std::ios::out);
    fs.close();
}
