#include "InputManager.h"

#include <fstream>
#include <boost/algorithm/string.hpp>


#include <iostream>
using namespace std;

InputManager::InputManager(string filename){

    fstream f;
    f.open(filename.c_str(),ios::in);
    string line;
    
    while ( getline (f,line) ){
        vector<string> strs;
        boost::split(strs,line,boost::is_any_of(":"));
        if (strs.size()>1){
            _inputs[strs[0]]=Input();
        }
        
    }
    
    _inputs["simulation"].inps["steps"]=100;
    
    
    
    
    f.close();
    
}
