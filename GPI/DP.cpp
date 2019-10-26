#include "GPI.h"
#include <map>
#include <stdlib.h>
#include "../Policy/TabularDeterminsticPolicy.h"

using namespace std;

template<class stateType, class actionType>
Policy<stateType, actionType>* GPI::DP
    (FullyModeledEnviroment<stateType, actionType>& env, double discount, double stoppingFactor)
{
    pair<stateType*, int> stateSpace = env.GetStates();
    pair<actionType*, int> actionSpace = env.GetActions();
    map<const stateType&, double> v;
    Policy<stateType, actionType>* policy;
    policy = new TabularDeterminsticPolicy<stateType, actionType>(env);
    bool updated;
    do
    {
        updated = false;
        for(int i = 0; i < stateSpace.second; i++)   
        {
            if(stateSpace.first[i].IsTerminal) continue;
            double maxVal = 0;
            const actionType& action;
            vector<pair<double, pair<const stateType&, int>>>* props;
            for(int j = 0; j < actionSpace.second; j++)
            {
                props = env.GetAllProbabilities(actionSpace.first[j], stateSpace.first[i]);
                double curVal = 0;
                for(auto k : *props)
                {
                    curVal += k.first * (k.second.second + (discount * v[k.second.first]));
                }
                delete props;
                if(curVal > maxVal)
                {
                    maxVal = curVal;
                    action = actionSpace.first[j];
                }
            }
            auto itr = v.find(stateSpace.first[i]);
            if(itr == v.end())
            {
                v[stateSpace.first[i]] = maxVal;
                policy->Learn(stateSpace.first[i], action);
                updated = true;
            }
            else
            {
                double curVal = itr->second;
                if(abs(curVal - maxVal) >= stoppingFactor)
                {
                    updated = true;
                    v[stateSpace.first[i]] = maxVal;
                    policy->Learn(stateSpace.first[i], action);
                }
            }
        }
    }
    while(updated);
    return policy;
}