#ifndef GPI_NAMESPACE   
#define GPI_NAMESPACE

#include "../Enviroment/FullyModeledEnviroment.cpp"
#include "../Policy/Policy.h"

namespace GPI
{
    template <class stateType, class actionType>
    Policy<stateType, actionType>* DP(FullyModeledEnviroment<stateType, actionType>& env,
                                      double discount, double stoppingFactor);

    template <class stateType, class actionType>
    Policy<stateType, actionType>* MonteCarlo(Enviroment<stateType, actionType>& env,
                                              double discount, double stoppingfactor, int episodeCount);

    template <class stateType, class actionType>
    Policy<stateType, actionType>* TD(Enviroment<stateType, actionType>& env,
                                      double discount, double stoppingfactor, int episodeCount);
}


#endif