#ifndef POLICY_CLASS
#define POLICY_CLASS

#include "../Enviroment/Enviroment.h"

template<class stateType, class actionType>
class Policy
{
private:
    Enviroment<stateType, actionType>& env;
protected:
    Policy(Enviroment<stateType, actionType>& env) {this->env = env;}
public:
    virtual const actionType& Act(const stateType& state) = 0;
    virtual void Learn(const stateType& state, const actionType& action) = 0;
};


#endif