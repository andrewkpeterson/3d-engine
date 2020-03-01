#include "Selector.h"

Selector::Selector()
{

}

Selector::~Selector()
{

}

void Selector::reset() {
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->reset();
    }
}

Status Selector::update(float seconds) {
    for (int i = 0; i < m_children.size(); i++) {
        Status s = m_children[i]->update(seconds);
        if (s == Status::RUNNING || s == Status::SUCCESS) {
            return s;
        }
    }

    return FAIL;
}
