#include "EquiProbablePolicy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

template<class stateType, class actionType>
const actionType& EquiProbablePolicy<stateType, actionType>::Act(const stateType& state)
{
    pair<const actionType* , int> actions = this->env.GetActions();
    srand(time(NULL));
    return actions.first[rand() % actions.second];
}

template<class stateType, class actionType>
void EquiProbablePolicy<stateType, actionType>::Learn(const stateType& state, const actionType& action)
{
    throw std::exception("You can't update the EquiProbable Policy");
}