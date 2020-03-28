#ifndef PLATFORMERAPPLICATION_H
#define PLATFORMERAPPLICATION_H

#include "src/engine/common/Application.h"
#include "src/engine/graphics/Graphics.h"
#include "src/engine/util/CommonIncludes.h"

class PlatformerApplication : public Application {

public:
    PlatformerApplication();
    ~PlatformerApplication() override;

    void restart() override;
};

#endif // PLATFORMERAPPLICATION_H
