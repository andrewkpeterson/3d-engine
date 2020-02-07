#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include "System.h"

class DrawSystem : public System
{
public:
    DrawSystem();
    ~DrawSystem() override;

    void draw(Graphics *g);


};

#endif // DRAWSYSTEM_H
