#ifndef DUNGEONAPPLICATION_H
#define DUNGEONAPPLICATION_H

#include "src/engine/common/Application.h"
#include "src/engine/graphics/Graphics.h"
#include "src/engine/util/CommonIncludes.h"

class DungeonApplication : public Application {

public:
    DungeonApplication();
    ~DungeonApplication();

    void restart() override;
};

#endif // DUNGEONAPPLICATION_H
