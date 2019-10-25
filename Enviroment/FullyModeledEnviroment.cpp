#include "FullyModeledEnviroment.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

template <class stateType, class actionType>
FullyModeledEnviroment<stateType, actionType>::FullyModeledEnviroment(
    stateType* stateSpace, int stateCount, stateType* startStates, int startStatesCount,
    actionType* actionSpace, int actionCount, 
    vector<pair<double, pair<const stateType&, int>>>* (*Model)(const actionType&, const stateType&))
    : Enviroment<stateType, actionType>(actionSpace, actionCount)
{
    this->stateSpace = stateSpace;
    this->startStates = startStates;
    this->startStatesCount = startStatesCount;
    this->stateCount = stateCount;
    this->Model = Model;
    this->currentState = nullptr;
}

template <class stateType, class actionType>
vector<pair<double, pair<const stateType&, int>>>* 
FullyModeledEnviroment<stateType, actionType>::GetAllProbabilities(const actionType& action, 
                                                                   const stateType& state)
{
    if(state == nullptr) state = this->currentState;
    return this->Model(action, state);
}

template <class stateType, class actionType>
pair<const stateType&, int> FullyModeledEnviroment<stateType, actionType>::Interact(const actionType& action)
{
    if(currentState == nullptr)
    {
        throw std::exception("The enviroment hasn't been intiated yet");
    }
    srand(time(NULL));
    int propability = rand() % 101;
    vector<pair<double, pair<const stateType&, int>>>* props = this->Model(action, *(this->currentState));
    for (int i = 0; i < props->size(); i++)
    {
        propability -= (int)(props->at(i).first * 100);
        if (propability <= 0)
        {
            auto res = props->at(i).second;
            delete props;
            this->currentState = &res.first;
            return res;
        }
    }
    delete props;
    throw std::exception("The provided enviroment model returned probabilites that don't add-up to 1");
}

template<class stateType, class actionType>
const stateType& FullyModeledEnviroment<stateType, actionType>::InitiateEnviroment()
{
    srand(time(NULL));
    this->currentState = startStates[rand() % startStatesCount];
    return *(this->currentState);
}
template<class stateType, class actionType>
const stateType& FullyModeledEnviroment<stateType, actionType>::GetCurrentState()
{
    return *(this->currentState);
}

template <class stateType, class actionType>
FullyModeledEnviroment<stateType, actionType>::~FullyModeledEnviroment()
{
    delete[] stateSpace;
}