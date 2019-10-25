#include "TabularDeterminsticPolicy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

template<class stateType, class actionType>
const actionType& TabularDeterminsticPolicy<stateType, actionType>::Act(const stateType& state)
{
    auto itr = policy.find(state);
    if(itr != policy.end())
    {
        return itr->second;
    }
    pair<const actionType* , int> actions = this->env.GetActions();
    srand(time(NULL));
    return actions.first[rand() % actions.second];
}

template<class stateType, class actionType>
void TabularDeterminsticPolicy<stateType, actionType>::Learn(const stateType& state, const actionType& action)
{
    policy[state] = action;
}