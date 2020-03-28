#ifndef ENVIRONMENTSYSTEM_H
#define ENVIRONMENTSYSTEM_H

#include "System.h"
#include "src/engine/common/component/EnvironmentComponent.h"

class EnvironmentSystem : public System
{
public:
    EnvironmentSystem(GameWorld *gameworld);
    ~EnvironmentSystem() override;

    void setEnvironment(std::shared_ptr<EnvironmentComponent> env);
    std::shared_ptr<EnvironmentComponent> getEnvironment();
    void drawEnvironment();

private:
    std::shared_ptr<EnvironmentComponent> environment;
    Graphics *g;

};

#endif // ENVIRONMENTSYSTEM_H
