#ifndef WARMUPAPPLICATION_H
#define WARMUPAPPLICATION_H

#include "src/engine/common/Application.h"

class WarmupApplication : public Application {

public:
    WarmupApplication();
    ~WarmupApplication();

    void startScreenToGameplayScreen();
    void restart();
};

#endif // WARMUPAPPLICATION_H
