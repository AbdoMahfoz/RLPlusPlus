#ifndef AGENT_CLASS
#define AGENT_CLASS

#include "../Enviroment/Enviroment.h"
#include "../Policy/Policy.h"
#include <stack>

template <class stateType, class actionType>
struct EpisodeHistory
{
public:
    const stateType& state, nextState;
    const actionType& action;
    int reward;
    EpisodeHistory(const stateType& state, const actionType& action, const stateType& nextState, int reward)
    {
        this->state = state;
        this->action = action;
        this->nextState = nextState;
        this->reward = reward;
    }
    EpisodeHistory() {}
};

template <class stateType, class actionType>
class EpisodicAgent
{
private:
    Enviroment<stateType, actionType>& env;
    Policy<stateType, actionType>& policy;
    stack<EpisodeHistory<stateType, actionType>> history;
    void (*interrupt)(const stateType&, const stateType&, int);
    bool recordHistory;
public:
    EpisodicAgent(Enviroment<stateType, actionType>& env, Policy<stateType, actionType>& policy, 
                  bool recordHistory, void (*interrupt)(const stateType&, const stateType&, int) = nullptr);
    void PlayAnEpisode();
    void ShouldRecordHistory(bool);
    stack<EpisodeHistory<stateType, actionType>>& GetHistory();
};

#endif