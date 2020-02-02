#ifndef WARMUPAPPLICATION_H
#define WARMUPAPPLICATION_H

#include "src/engine/common/Application.h"
#include "src/engine/graphics/Graphics.h"
#include "src/engine/util/CommonIncludes.h"

class WarmupApplication : public Application {

public:
    WarmupApplication();
    ~WarmupApplication();

    void restart() override;
};

#endif // WARMUPAPPLICATION_H
