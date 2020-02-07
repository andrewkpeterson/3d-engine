#include "GameWorld.h"
#include "system/DrawSystem.h"
#include "system/TickSystem.h"
#include "system/CollisionSystem.h"

GameWorld::GameWorld()
{
    addSystem<DrawSystem>(std::make_shared<DrawSystem>());
    std::cout << getSystem<DrawSystem>()->getName() << std::endl;
    addSystem<TickSystem>(std::make_shared<TickSystem>());
    std::cout << getSystem<DrawSystem>()->getName() << std::endl;
    addSystem<CollisionSystem>(std::make_shared<CollisionSystem>());
    std::cout << getSystem<CollisionSystem>()->getName() << std::endl;

    auto it = sys.begin();
    while (it != sys.end()) {
        std::cout << it->second->draw() << std::endl;
        it++;
    }
    removeSystem<DrawSystem>();
    removeSystem<TickSystem>();
    std::cout << getSystem<CollisionSystem>()->getName() << std::endl;
    removeSystem<CollisionSystem>();
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

/*
std::shared_ptr<System> GameWorld::getSystem(std::string name) {
    return m_systems.at(name);
}
*/
