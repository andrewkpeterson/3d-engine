#ifndef BTNODE_H
#define BTNODE_H

#include "src/engine/common/component/Component.h"

enum Status {
    SUCCESS, FAIL, RUNNING
};

class BTNode
{
public:
    BTNode(Component *component);
    virtual ~BTNode();
    virtual Status update(float seconds) = 0;
    virtual void reset() = 0;

protected:
    Component *m_component;
};

#endif // BTNODE_H
