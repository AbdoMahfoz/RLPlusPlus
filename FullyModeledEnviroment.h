#ifndef FULLYMODELEDENVIROMENT_CLASS
#define FULLYMODELEDENVIROMENT_CLASS

#include "Enviroment.h"

using namespace std;

template <class stateType, class actionType>
class FullyModeledEnviroment : public Enviroment<stateType, actionType>
{
private:
    stateType *stateSpace, *startStates, *currentState;
    int stateCount, startStatesCount;
    vector<pair<double, pair<const stateType& , int>>>* (*Model)(const actionType&, const stateType&);

public:
    FullyModeledEnviroment(stateType* stateSpace, int stateCount,
                           stateType* startStates, int startStatesCount,
                           actionType* actionSpace, int actionCount,
                           vector<pair<double, pair<const stateType&, int>>>* (*Model)(const actionType&, const stateType&));
    pair<const stateType&, int> Interact(const actionType& action);
    const stateType& InitiateEnviroment();
    vector<pair<double, pair<const stateType&, int>>>* GetAllProbabilities(const actionType& action, const stateType& state);
    pair<const stateType*, int> GetStates();
    const stateType& GetCurrentState();
    virtual ~FullyModeledEnviroment();
};

#endif