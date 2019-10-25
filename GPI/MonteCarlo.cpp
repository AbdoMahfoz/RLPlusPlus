#include "GPI.h"
#include "../Agents/EpisodicAgent.cpp"
#include "../Policy/EquiProbablePolicy.cpp"
#include <set>
#include <map>

template <class stateType, class actionType>
Policy<stateType, actionType>* GPI::MonteCarlo(Enviroment<stateType, actionType>& env,
                                               double discount, double stoppingfactor, int episodeCount)
{
    pair<actionType*, int> actionSpace = env.GetActions();
    EquiProbablePolicy<stateType, actionType> exploringPolicy(env);
    Policy<stateType, actionType>* resPolicy;
    resPolicy = new TabularDeterminsticPolicy<stateType, actionType>(env);
    EpisodicAgent<stateType, actionType> agent(env, exploringPolicy, true);
    map<pair<const stateType&, const actionType&>, double> q, c;
    set<const stateType&> visitedStates;
    for(int i = 0; i < episodeCount; i++)
    {
        agent.PlayAnEpisode();
        stack<EpisodeHistory<stateType, actionType>>& history = agent.GetHistory();
        double reward = 0, w = 1;
        while(!history.empty())
        {
            EpisodeHistory<stateType, actionType> entry = history.front();
            visitedStates.insert(entry.state);
            history.pop();
            reward = entry.reward + (discount * reward); 
            double cVal = c[{entry.state, entry.action}];
            c[{entry.state, entry.action}] += w;
            q[{entry.state, entry.action}] += (w / (w + cVal)) * (reward - q[{entry.state, entry.action}]);
            w *= ((resPolicy->Act(entry.state) == entry.action) ? actionSpace.second : 0.0);
        }
        for(auto s : visitedStates)
        {
            double maxVal = 0;
            int maxAction;
            for(int i = 0; i < actionSpace.second; i++)
            {
                double val = q[{s, actionSpace.first[i]}];
                if(val > maxVal)
                {
                    maxVal = val;
                    maxAction = i;
                }
            }
            resPolicy->Learn(s, actionSpace.first[maxAction]);
        }
        visitedStates.clear();
    }
    return resPolicy;
}