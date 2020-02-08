#include "System.h"

System::System(std::string str, std::shared_ptr<GameWorld> gameworld) :
    name(str),
    m_gameworld(gameworld)
{

}

System::~System()
{

}

void System::tick() {

}

void System::addGameObject(std::shared_ptr<GameObject> gameobject) {
    m_gameobjects.insert(gameobject);
}

void System::removeGameObject(std::shared_ptr<GameObject> gameobject) {
    m_gameobjects.erase(gameobject);
}

const std::string System::getName() {
    return name;
}
