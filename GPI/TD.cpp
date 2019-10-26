#include "GPI.h"
#include "../Agents/EpisodicAgent.cpp"
#include "../Policy/TabularDeterministicPolicy.cpp"
#include "EpisodicAgentInterruptor.h"

#ifndef TDSOLVER_CLASS
#define TDSOLVER_CLASS

template <class stateType, class actionType>
class TDSolver : public EpisodicAgentInterruptor<stateType, actionType>
{
private:
    pair<actionType*, int> actionSpace;
    Enviroment<stateType, actionType>& env;
    Policy<stateType, actionType>& resPolicy;
    EpisodicAgent<stateType, actionType>& agent;
    map<const stateType&, double> v;
    double discount, stoppingfactor, learningFactor;
    int episodeCount;
    void Interrupt(const stateType& state, const actionType& action, 
                   const stateType& nextState, int reward)
    {
        v[state] += learningFactor * (reward + (discount * v[nextState]) - v[state]);
    }
public:
    TDSolver(Enviroment<stateType, actionType>& env, Policy<stateType, actionType>& policy,
             EpisodicAgent<stateType, actionType>& agent,
             double discount, double stoppingfactor, int episodeCount, double learningFactor)
    : EpisodicAgentInterruptor<stateType, actionType>(agent)
    {
        this->env = env;
        this->resPolicy = policy;
        this->agent = agent;
        this->discount = discount;
        this->stoppingfactor = stoppingfactor;
        this->episodeCount = episodeCount;
        this->learningFactor = learningFactor;
        this->actionSpace = env.GetActions();
    }
};

#endif

template <class stateType, class actionType>
Policy<stateType, actionType>* GPI::TD
    (Enviroment<stateType, actionType>& env, double discount, double stoppingfactor, 
    int episodeCount, double learningFactor)
{
    throw std::exception("TD is not fully implemented yet");
    Policy<stateType, actionType>* policy = new TabularDeterminsticPolicy<stateType, actionType>(env);
    EpisodicAgent<stateType, actionType> agent(env, policy, false);
    TDSolver<stateType, actionType> Solver(env, policy, agent, discount, stoppingfactor, 
                                           episodeCount, learningFactor);
    for(int i = 0; i < episodeCount; i++)
    {
        agent.PlayAnEpisode();
    }
    return policy;
}