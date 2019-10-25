#include "InteractiveEnviroment.h"

template<class stateType, class actionType>
InteractiveEnviroment<stateType, actionType>::InteractiveEnviroment(
    actionType* actionSpace, int actionSpaceCount,
    pair<const stateType&, int> (*Interact)(const actionType&),
    const stateType& (*Initiate)())
    : Enviroment<stateType, actionType>(actionSpace, actionSpaceCount)
{
    this->InteractPtr = Interact;
    this->InitiatePtr = Initiate;
}

template<class stateType, class actionType>
pair<const stateType&, int> InteractiveEnviroment<stateType, actionType>::Interact(const actionType& action)
{
    return this->InteractPtr(action);
}

template<class stateType, class actionType>
const stateType& InteractiveEnviroment<stateType, actionType>::InitiateEnviroment()
{
    return this->InitiatePtr();
}