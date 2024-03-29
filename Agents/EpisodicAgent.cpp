#include "EpisodicAgent.h"

template <class stateType, class actionType>
EpisodicAgent<stateType, actionType>::EpisodicAgent
    (Enviroment<stateType, actionType>& env, Policy<stateType, actionType>& policy, bool recordHistory,
     void (*interrupt)(const stateType&, const actionType&, const stateType&, int, void*))
{
    this->env = env;
    this->policy = policy;
    this->recordHistory = recordHistory;
    this->interrupt = interrupt;
}

template <class stateType, class actionType>
void EpisodicAgent<stateType, actionType>::PlayAnEpisode()
{
    const stateType& curState = env.InitiateEnviroment();
    if(recordHistory)
        while(!history.empty()) history.pop();
    while(!curState.IsTerminal)
    {
        const actionType& action = policy.Act(curState);
        pair<const stateType&, int> result = env.Interact(action);
        if(recordHistory) history.push(EpisodeHistory<stateType, actionType>(curState, action, 
                                                                             result.first, result.second));
        if(interrupt != nullptr) interrupt(curState, action, result.first, result.second, this);
        curState = result.first;
    }
}

template <class stateType, class actionType>
void EpisodicAgent<stateType, actionType>::ShouldRecordHistory(bool val)
{
    this->recordHistory = val;
}

template <class stateType, class actionType>
void EpisodicAgent<stateType, actionType>::SetInterrupt(void (*interrupt)(const stateType&, 
    const actionType&, const stateType&, int, void*))
{
    this->interrupt = interrupt;
}

template <class stateType, class actionType>
stack<EpisodeHistory<stateType, actionType>>& EpisodicAgent<stateType, actionType>::GetHistory()
{
    return this->history;
}