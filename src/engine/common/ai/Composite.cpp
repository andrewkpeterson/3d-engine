#include "Composite.h"

Composite::Composite(Component *component, std::vector<std::shared_ptr<BTNode>> children) :
    BTNode (component),
    m_children(children)
{

}

Composite::~Composite()
{

}
