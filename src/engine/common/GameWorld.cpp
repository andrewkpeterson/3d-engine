#include "GameWorld.h"
#include "system/DrawSystem.h"
#include "system/TickSystem.h"
#include "system/CollisionSystem.h"
#include "system/ControlCallbackSystem.h"
#include "component/DrawableComponent.h"
#include "component/TransformComponent.h"

GameWorld::GameWorld(Screen *screen) :
    m_screen(screen)
{

}

GameWorld::~GameWorld()
{

}

void GameWorld::tick(float seconds) {
    getSystem<TickSystem>()->tick(seconds);
}

void GameWorld::draw(Graphics *g) {
    getSystem<DrawSystem>()->draw(g);
}

void GameWorld::resize(int width, int height) {

}

void GameWorld::addGameObject(std::shared_ptr<GameObject> object) {
    m_gameobjects.insert(object);
    object->addSelfToSystems();
}

void GameWorld::removeGameObject(std::shared_ptr<GameObject> object) {
    object->removeSelfFromSystems();
    m_gameobjects.erase(object);
}

void GameWorld::onKeyPressed(QKeyEvent *event) {
    getSystem<ControlCallbackSystem>()->onKeyPressed(event);
}

void GameWorld::onKeyReleased(QKeyEvent *event) {
    getSystem<ControlCallbackSystem>()->onKeyReleased(event);
}

void GameWorld::onKeyRepeated(QKeyEvent *event) {
    getSystem<ControlCallbackSystem>()->onKeyRepeated(event);
}

void GameWorld::onMousePressed(QMouseEvent *event) {
    getSystem<ControlCallbackSystem>()->onMousePressed(event);
}

void GameWorld::onMouseReleased(QMouseEvent *event) {
    getSystem<ControlCallbackSystem>()->onMouseReleased(event);
}

void GameWorld::onMouseDragged(int deltaX, int deltaY) {
    getSystem<ControlCallbackSystem>()->onMouseDragged(deltaX, deltaY);
}

void GameWorld::onWheelEvent(QWheelEvent *event) {
    getSystem<ControlCallbackSystem>()->onWheelEvent(event);
}
