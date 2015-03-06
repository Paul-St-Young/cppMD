#include "AndersonThermostat.h"

#include <random>

using namespace std;

void AndersonThermostat::apply(){
if ( _keep || _mystep<_nequil ){
    random_device rd;
    mt19937 mt(rd());
    normal_distribution<RealType> normal(0,sqrt(_T/_m));
    uniform_real_distribution<RealType> rand(0,1);
    
    
    RealType collisionProb = _eta*_h;
    for (int i=0;i<_pset.n;i++){
        if (rand(mt)<collisionProb){
            for (int coord=0;coord<_MD_DIM;coord++){
                _pset.ptcls[i]->v[coord]=normal(mt);
            }
        }
    }
_mystep++;
}
}

