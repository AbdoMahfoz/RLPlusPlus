#include "Enviroment.h"

template <class stateType, class actionType>
Enviroment<stateType, actionType>::Enviroment(actionType* actionSpace, int actionCount)
{
    this->actionSpace = actionSpace;
    this->actionCount = actionCount;
}

template <class stateType, class actionType>
pair<const actionType* , int> Enviroment<stateType, actionType>::GetActions()
{
    return {this->actionSpace, this->actionCount};
}

template <class stateType, class actionType>
Enviroment<stateType, actionType>::~Enviroment()
{
    delete[] actionSpace;
}