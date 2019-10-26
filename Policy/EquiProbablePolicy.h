#ifndef EQUIPROBABLEPOLICY_CLASS
#define EQUIPROBABLEPOLICY_CLASS

#include "Policy.h"

template<class stateType, class actionType>
class EquiProbablePolicy : public Policy<stateType, actionType>
{
public:
    EquiProbablePolicy(Enviroment<stateType, actionType>& env) : Policy<stateType, actionType>(env) {}
    const actionType& Act(const stateType& state);
    void Learn(const stateType& state, const actionType& action);
};

#endif