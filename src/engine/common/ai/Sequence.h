#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Composite.h"

class Sequence : public Composite
{
public:
    Sequence();
    ~Sequence();
    void reset() override;
    Status update(float seconds) override;

private:
    int last_running_idx;
};

#endif // SEQUENCE_H
