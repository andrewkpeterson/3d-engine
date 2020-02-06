#ifndef SYSTEM_H
#define SYSTEM_H

#include "src/engine/util/CommonIncludes.h"
#include "src/engine/util/TypeMap.h"
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
    void addGameObject(std::shared_ptr<GameObject>); //what should this take in??
    void removeGameObject(std::shared_ptr<GameObject>); //what should this take in??

protected:
    TypeMap<std::shared_ptr<GameObject>> m_gameobjects;
};

#endif // SYSTEM_H
