#ifndef GPI_NAMESPACE   
#define GPI_NAMESPACE

#include "../Enviroment/FullyModeledEnviroment.h"
#include "../Policy/Policy.h"

namespace GPI
{
    template <class stateType, class actionType, class policyType>
    Policy<stateType, actionType>* DP(FullyModeledEnviroment<stateType, actionType>& env,
                                      double discount, double stoppingFactor);

    template <class stateType, class actionType, class policyType>
    Policy<stateType, actionType>* MonteCarlo(Enviroment<stateType, actionType>& env,
                                              double discount, double stoppingfactor,
                                              double learningFator, int episodeCount);
}


#endif