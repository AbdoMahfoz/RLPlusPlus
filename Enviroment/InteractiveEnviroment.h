#ifndef INTERACTIVEENVIROMENT_CLASS
#define INTERACTIVEENVIROMENT_CLASS

#include "Enviroment.h"

template<class stateType, class actionType>
class InteractiveEnviroment : public Enviroment<stateType, actionType>
{
private:
    pair<const stateType&, int> (*InteractPtr)(const actionType&);
    const stateType& (*InitiatePtr)();
public:
    InteractiveEnviroment(actionType* actionSpace, int actionSpaceCount,
                          pair<const stateType&, int> (*Interact)(const actionType&),
                          const stateType& (*Initiate)());
    pair<const stateType&, int> Interact(const actionType& action);
    const stateType& InitiateEnviroment();
};

#endif