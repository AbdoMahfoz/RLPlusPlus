#ifndef GPI_NAMESPACE   
#define GPI_NAMESPACE

#include "../Enviroment/FullyModeledEnviroment.h"
#include "../Policy/TabularDeterminsticPolicy.h"

namespace GPI
{
    template<class stateType, class actionType>
    TabularDeterminsticPolicy<stateType, actionType>* DP(FullyModeledEnviroment<stateType, actionType>& env,
                                                         double discount, double stoppingFactor);
}


#endif