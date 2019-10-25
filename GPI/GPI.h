#ifndef GPI_NAMESPACE   
#define GPI_NAMESPACE

#include "../Enviroment/FullyModeledEnviroment.h"
#include "../Policy/TabularDeterminsticPolicy.h"

namespace GPI
{
    template <class stateType, class actionType>
    Policy<stateType, actionType>* DP(FullyModeledEnviroment<stateType, actionType>& env,
                                      double discount, double stoppingFactor);

    template <class stateType, class actionType>
    Policy<stateType, actionType>* MonteCarlo(Enviroment<stateType, actionType>& env,
                                              double discount, double stoppingfactor, int episodeCount);
}


#endif