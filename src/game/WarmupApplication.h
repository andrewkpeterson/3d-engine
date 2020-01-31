#ifndef WARMUPAPPLICATION_H
#define WARMUPAPPLICATION_H

#include "src/engine/common/Application.h"
#include "src/engine/graphics/Graphics.h"

class WarmupApplication : public Application {

public:
    WarmupApplication(Graphics *g);
    ~WarmupApplication();

    void startScreenToGameplayScreen();
    void restart();
};

#endif // WARMUPAPPLICATION_H
