#ifndef CONDITION_H
#define CONDITION_H

#include "BTNode.h"

class Condition : public BTNode
{
public:
    Condition(Component *component);
    virtual ~Condition();
};

#endif // CONDITION_H
