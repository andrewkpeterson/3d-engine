#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include "System.h"

class DrawSystem : public System
{
public:
    DrawSystem(std::shared_ptr<GameWorld> gameworld);
    ~DrawSystem() override;

    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::shared_ptr<Component> component);

    void draw(Graphics *g);

private:
    Graphics *g;
};

#endif // DRAWSYSTEM_H
