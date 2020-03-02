#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "BTNode.h"
#include <vector>
#include <memory>

class Composite : public BTNode
{
public:
    Composite(Component *component, std::vector<std::shared_ptr<BTNode>> children);
    ~Composite();

protected:
    std::vector<std::shared_ptr<BTNode>> m_children;
    std::shared_ptr<BTNode> m_lastrunning;
};

#endif // COMPOSITE_H
