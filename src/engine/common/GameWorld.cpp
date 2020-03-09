#include "GameWorld.h"
#include "system/DrawSystem.h"
#include "system/TickSystem.h"
#include "system/CollisionSystem.h"
#include "system/ControlCallbackSystem.h"
#include "component/DrawableComponent.h"
#include "component/TransformComponent.h"
#include "system/ChunkStreamingSystem.h"
#include "system/OrthographicUISystem.h"
#include "system/UISystem.h"
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
    addSystem<OrthographicUISystem>(std::make_shared<OrthographicUISystem>(this));
    addSystem<UISystem>(std::make_shared<UISystem>(this));
}

GameWorld::~GameWorld()
{

}

void GameWorld::tick(float seconds) {
    getSystem<TickSystem>()->tick(seconds);
    getSystem<CollisionSystem>()->checkForCollisions(seconds);
    getSystem<ChunkStreamingSystem>()->buildEnqueuedChunk();
    //getSystem<ChunkStreamingSystem>()->destroyOldChunks();
    removeGameObjectsMarkedForDeletion();
}

void GameWorld::draw(Graphics *g) {
    getSystem<DrawSystem>()->draw(g);
    if (m_activeui != nullptr) {
        //m_activeui->drawUI();
    }
    getSystem<OrthographicUISystem>()->draw(g);
    getSystem<UISystem>()->draw(g);
}

void GameWorld::resize(int width, int height) {
    getSystem<CameraSystem>()->resizeCameras(width, height);
    auto it = m_uis.begin();
    while (it != m_uis.end()) {
        it->second->resize(width, height);
        it++;
    }
    getSystem<OrthographicUISystem>()->resizeCamera(width, height);
    getSystem<UISystem>()->resizeCamera(width, height);
}

void GameWorld::addGameObject(std::shared_ptr<GameObject> object) {
    //assert(m_gameobjects.find(object->getID()) == m_gameobjects.end());
    if (m_gameobjects.find(object->getID()) == m_gameobjects.end()) {
        m_gameobjects.insert({object->getID(), object});
        object->setGameWorld(this);
        object->addSelfToSystems();
    }
}

void GameWorld::removeGameObject(std::shared_ptr<GameObject> object) {
    assert(m_gameobjects.find(object->getID()) != m_gameobjects.end());
    object->removeSelfFromSystems();
    m_gameobjects.erase(object->getID());
}

void GameWorld::removeGameObject(std::string id) {
    assert(m_gameobjects.find(id) != m_gameobjects.end());
    m_gameobjects[id]->removeSelfFromSystems();
    m_gameobjects.erase(m_gameobjects[id]->getID());
}

void GameWorld::onKeyPressed(QKeyEvent *event) {
    getSystem<ControlCallbackSystem>()->onKeyPressed(event);
}

void GameWorld::markGameObjectForDeletion(std::string id) {
    ids_to_delete.push_back(id);
}

void GameWorld::removeGameObjectsMarkedForDeletion() {
    for (int i = 0; i < ids_to_delete.size(); i++) {
        removeGameObject(ids_to_delete[i]);
    }
    ids_to_delete.clear();
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
