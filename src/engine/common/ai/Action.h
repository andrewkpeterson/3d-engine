#ifndef ACTION_H
#define ACTION_H

#include "BTNode.h"

class Action : public BTNode
{
public:
    Action(Component *component);
    ~Action();
};

#endif // ACTION_H
