#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Composite.h"

class Sequence : public Composite
{
public:
    Sequence(Component *component, std::vector<std::shared_ptr<BTNode>> children);
    ~Sequence();
    void reset() override;
    Status update(float seconds) override;

private:
    int last_running_idx;
};

#endif // SEQUENCE_H
