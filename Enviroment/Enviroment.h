#ifndef ENVIROMENT_CLASS
#define ENVIROMENT_CLASS

#include <vector>

using namespace std;

template <class stateType, class actionType>
class Enviroment
{
private:
    actionType* actionSpace;
    int actionCount;

protected:
    Enviroment(actionType *actionSpace, int actionCount);

public:
    virtual pair<const stateType&, int> Interact(const actionType& action) = 0;
    virtual const stateType& InitiateEnviroment() = 0;
    pair<const actionType* , int> GetActions();
    virtual ~Enviroment();
};

#endif