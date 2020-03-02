#include "Sequence.h"

Sequence::Sequence(Component *component, std::vector<std::shared_ptr<BTNode> > children) :
    Composite (component, children),
    last_running_idx(0)
{

}

Sequence::~Sequence()
{

}

void Sequence::reset() {
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->reset();
    }
}

Status Sequence::update(float seconds) {
    for (int i = last_running_idx; i < m_children.size(); i++) {
        Status s = m_children[i]->update(seconds);
        if (s == Status::RUNNING) {
            last_running_idx = i;
            return s;
        } else if (s == Status::FAIL) {
            last_running_idx = 0;
            return s;
        }
    }

    last_running_idx = 0;
    return SUCCESS;
}
