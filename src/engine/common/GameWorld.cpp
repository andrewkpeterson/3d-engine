#include "GameWorld.h"

GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{

}

void GameWorld::tick() {

}

void GameWorld::draw(Graphics *g) {
    m_systems["DrawSystem"]->draw(g);
}

void GameWorld::addSystem(std::shared_ptr<System> system) {
    m_systems[system->getName()] = system;
}

void GameWorld::removeSystem(std::shared_ptr<System> system) {
    m_systems.erase(system->getName());
}

void GameWorld::addGameObject(std::shared_ptr<GameObject> object) {
    m_gameobjects.insert(object);
    object->addComponentsToSystems();
}

void GameWorld::removeGameObject(std::shared_ptr<GameObject> object) {
    object->removeComponentsFromSystems();
    m_gameobjects.erase(object);
}

std::shared_ptr<System> GameWorld::getSystem(std::string name) {
    return m_systems.at(name);
}
