#include "GameWorld.h"
#include "system/DrawSystem.h"
#include "system/TickSystem.h"
#include "system/CollisionSystem.h"
#include "component/DrawableComponent.h"
#include "component/TransformComponent.h"

GameWorld::GameWorld()
{
    std::shared_ptr<GameObject> go1 = std::make_shared<GameObject>();
    go1->addComponent<DrawableComponent>(std::make_shared<DrawableComponent>());
    std::shared_ptr<GameObject> go2 = std::make_shared<GameObject>();
    go2->addComponent<TransformComponent>(std::make_shared<TransformComponent>());
    addGameObject(go1);
    addGameObject(go2);
    std::shared_ptr<GameObject> go3 = go2;
    removeGameObject(go3);
    removeGameObject(go1);
}

GameWorld::~GameWorld()
{

}

void GameWorld::tick() {

}

void GameWorld::draw(Graphics *g) {
    getSystem<DrawSystem>()->draw(g);
}

/*
void GameWorld::addSystem(std::shared_ptr<System> system) {
    m_systems[system->getName()] = system;
}
*/

/*
void GameWorld::removeSystem(std::shared_ptr<System> system) {
    m_systems.erase(system->getName());
}
*/

void GameWorld::addGameObject(std::shared_ptr<GameObject> object) {
    m_gameobjects.insert(object);
    object->addComponentsToSystems();
}

void GameWorld::removeGameObject(std::shared_ptr<GameObject> object) {
    object->removeComponentsFromSystems();
    m_gameobjects.erase(object);
}

/*
std::shared_ptr<System> GameWorld::getSystem(std::string name) {
    return m_systems.at(name);
}
*/
