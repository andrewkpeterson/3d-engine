#include "GameWorld.h"
#include "system/DrawSystem.h"
#include "system/TickSystem.h"
#include "system/CollisionSystem.h"
#include "system/ControlCallbackSystem.h"
#include "component/DrawableComponent.h"
#include "component/TransformComponent.h"
#include "system/ChunkStreamingSystem.h"
#include "src/engine/common/ui/UI.h"

GameWorld::GameWorld(Screen *screen) :
    m_screen(screen),
    m_activeui(nullptr)
{
    addSystem<DrawSystem>(std::make_shared<DrawSystem>(this));
    addSystem<TickSystem>(std::make_shared<TickSystem>(this));
    addSystem<ControlCallbackSystem>(std::make_shared<ControlCallbackSystem>(this));
    addSystem<CollisionSystem>(std::make_shared<CollisionSystem>(this));
    addSystem<CameraSystem>(std::make_shared<CameraSystem>(this));
    addSystem<ChunkStreamingSystem>(std::make_shared<ChunkStreamingSystem>(this));
}

GameWorld::~GameWorld()
{

}

void GameWorld::tick(float seconds) {
    getSystem<TickSystem>()->tick(seconds);
    getSystem<CollisionSystem>()->checkForCollisions(seconds);
    getSystem<ChunkStreamingSystem>()->buildEnqueuedChunk();
    getSystem<ChunkStreamingSystem>()->destroyBuiltChunk();
}

void GameWorld::draw(Graphics *g) {
    getSystem<DrawSystem>()->draw(g);
    if (m_activeui != nullptr) {
        m_activeui->drawUI();
    }
}

void GameWorld::resize(int width, int height) {
    getSystem<CameraSystem>()->resizeCameras(width, height);
    auto it = m_uis.begin();
    while (it != m_uis.end()) {
        it->second->resize(width, height);
        it++;
    }
}

void GameWorld::addGameObject(std::shared_ptr<GameObject> object) {
    assert(m_gameobjects.find(object->getID()) == m_gameobjects.end());
    m_gameobjects.insert({object->getID(), object});
    object->setGameWorld(this);
    object->addSelfToSystems();
}

void GameWorld::removeGameObject(std::shared_ptr<GameObject> object) {
    assert(m_gameobjects.find(object->getID()) != m_gameobjects.end());
    object->removeSelfFromSystems();
    m_gameobjects.erase(object->getID());
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

void GameWorld::addUI(std::shared_ptr<UI> ui, std::string name) {
    m_uis[name] = ui;
    ui->setGameWorld(this);
}

std::shared_ptr<UI> GameWorld::getActiveUI() {
    return m_activeui;
}

void GameWorld::setActiveUI(std::string name) {
    m_activeui = m_uis[name];
}

Screen *GameWorld::getScreen() {
    return m_screen;
}

std::shared_ptr<GameObject> GameWorld::getGameObjectByID(std::string id) {
    assert(m_gameobjects.find(id) != m_gameobjects.end());
    return m_gameobjects[id];
}
