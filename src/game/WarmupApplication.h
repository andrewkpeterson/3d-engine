#ifndef WARMUPAPPLICATION_H
#define WARMUPAPPLICATION_H

#include "src/engine/common/Application.h"

class WarmupApplication : public Application {
    WarmupApplication();
    ~WarmupApplication();

    virtual void tick(float dt);
    virtual void draw(Graphics &g);
};

#endif // WARMUPAPPLICATION_H
