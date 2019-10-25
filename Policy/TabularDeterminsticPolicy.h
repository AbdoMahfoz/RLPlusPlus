#ifndef TABULARPOLICY_CLASS
#define TABULARPOLICY_CLASS

#include "Policy.h"
#include <map>

template<class stateType, class actionType>
class TabularDeterminsticPolicy : public Policy<stateType, actionType>
{
private:
    std::map<const stateType&, const actionType&> policy;
public:
    TabularDeterminsticPolicy(Enviroment<stateType, actionType>& env) : Policy(env) {}
    const actionType& Act(const stateType& state);
    void Learn(const stateType& state, const actionType& action);
};

#endif