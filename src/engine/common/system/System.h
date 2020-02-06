#ifndef SYSTEM_H
#define SYSTEM_H

#include "src/engine/util/CommonIncludes.h"
#include <memory>
#include <vector>

class Graphics;
class System;
class GameObject;

class System
{
public:
    System();
    ~System();

    void tick();
    void addGameObject(); //what should this take in??
    void removeGameObject(); //what should this take in??

private:
    std::vector<GameObject> game_objects;
};

#endif // SYSTEM_H
