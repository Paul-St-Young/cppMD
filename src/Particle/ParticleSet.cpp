#include <iostream>
#include <fstream>

#include "ParticleSet.h"

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

/*
void ParticleSet::readPositions(std::string filename){
    std::ifstream fs;
    fs.open(filename.c_str());
    std::string line;
    if (fs.is_open()){
        while (getline(fs,line)){
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;

            // assuming: name, x, y, z, etc.
            std::vector<std::string> tokens(beg, end);
            for (int i=0;i<tokens.size();i++){
                std::cout << tokens[i] << std::endl;
            }
        }
    }
    fs.close();
}*/
