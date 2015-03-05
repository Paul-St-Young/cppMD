#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include "TypeFactory.h"

#include <map>

class Input{
public:
    std::map<std::string,std::string> inps;
};


class InputManager{
std::map<std::string,Input> _inputs;
public:
    InputManager(std::string filename);
    Input operator[](std::string input){ return _inputs[input]; };
};



#endif
