#ifndef SELECTOR_H
#define SELECTOR_H

#include "Composite.h"

class Selector : public Composite
{
public:
    Selector();
    ~Selector() override;
    void reset() override;
    Status update(float seconds) override;
};

#endif // SELECTOR_H
