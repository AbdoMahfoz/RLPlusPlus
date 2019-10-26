#ifndef EPISODICAGENTINTERRUPTOR_CLASS  
#define EPISODICAGENTINTERRUPTOR_CLASS

#include <map>
#include "../Agents/EpisodicAgent.h"

using namespace std;

template <class stateType, class actionType>
class EpisodicAgentInterruptor
{
private:
    void* key;
    static map<void*, EpisodicAgentInterruptor*> instances;
    static void CallBack(const stateType& state, const actionType& action, 
                         const stateType& nextState, int reward, void* key)
    {
        instances[key]->Interrupt(state, action, nextState, reward);
    }
protected:
    virtual void Interrupt(const stateType& state, const actionType& action, 
                           const stateType& nextState, int reward) = 0;
    EpisodicAgentInterruptor(EpisodicAgent<stateType, actionType>& agent)
    {
        this->key = &agent;
        instances[this->key] = this;
        agent.SetInterrupt(CallBack);
    }
    virtual ~EpisodicAgentInterruptor()
    {
        instances.erase(instances.find(this->key));
    }
};

#endif