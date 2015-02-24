#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <cstdlib>

#include "ParticlePool.h"

ParticlePool::ParticlePool(int n) : _n(n), _initialized(true) {
    for (int i=0;i<n;i++){
        _ptls.push_back(new Particle);
    }
}

void ParticlePool::readPositions(std::string filename){

    std::string line;
    std::ifstream fs;
    fs.open(filename.c_str());
    int line_num=0;
    if (fs.is_open()){
        while (getline(fs,line)){
            if (_initialized){
                std::istringstream buf(line);
                std::istream_iterator<std::string> beg(buf), end;
                
                // assuming: name, x, y, z, etc.
                std::vector<std::string> tokens(beg, end);
                _ptls[line_num]->name=tokens[0];
                for (int coord=0;coord<_MD_DIM;coord++){
                    _ptls[line_num]->r[coord]=atof(tokens[coord+1].c_str());
                }
                line_num++;
            }
        }/*
        if (!_initialized){
            fs.clear();                 // clear fail and eof bits
            fs.seekg(0, std::ios::beg);
            n=line_num;
            for (int i=0;i<n;i++){
                _ptls.push_back(new Particle);
            }
        }
        while (getline(fs,line)){
            if (_initialized){
                std::istringstream buf(line);
                std::istream_iterator<std::string> beg(buf), end;
                
                // assuming: name, x, y, z, etc.
                std::vector<std::string> tokens(beg, end);
                _ptls[line_num]->name=tokens[0];
                for (int coord=0;coord<_MD_DIM;coord++){
                    _ptls[line_num]->r[coord]=atof(tokens[coord+1].c_str());
                }
                line_num++;
            }
        }*/
    }
    fs.close();
    
}

void ParticlePool::readVelocities(std::string filename){
    std::fstream fs;
    fs.open(filename.c_str());
    int line_num=0;
    std::string line;
    if (fs.is_open()){
        while (getline(fs,line)){
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            
            // assuming: name, x, y, z, etc.
            std::vector<std::string> tokens(beg, end);
            for (int coord=0;coord<_MD_DIM;coord++){
                _ptls[line_num]->v[coord]=atof(tokens[coord+1].c_str());
            }
            line_num++;
        }
    }
    fs.close();

}


ParticlePool::~ParticlePool(){
    if (_initialized){
        for (int i=0;i<_n;i++){
            delete _ptls[i];
        }
    }
}
