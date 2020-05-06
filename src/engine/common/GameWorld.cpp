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
#include "system/EnvironmentSystem.h"
#include "system/AnimationSystem.h"
#include "src/engine/common/ui/UI.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>


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
    addSystem<EnvironmentSystem>(std::make_shared<EnvironmentSystem>(this));
    addSystem<AnimationSystem>(std::make_shared<AnimationSystem>(this));
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
    getSystem<UISystem>()->tick(seconds);
    getSystem<AnimationSystem>()->tick(seconds);
}

void GameWorld::draw(Graphics *g) {
    g->setCamera(getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera());
    g->drawSkybox();
    getSystem<DrawSystem>()->draw(g);
    getSystem<AnimationSystem>()->draw(g);
    getSystem<EnvironmentSystem>()->drawEnvironment();
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
    m_mutex.lock();
    assert(m_gameobjects.find(object->getID()) == m_gameobjects.end());
    if (m_gameobjects.find(object->getID()) == m_gameobjects.end()) {
        m_gameobjects.insert({object->getID(), object});
        object->setGameWorld(this);
        object->addSelfToSystems();
    }
    m_mutex.unlock();
}

void GameWorld::removeGameObject(std::shared_ptr<GameObject> object) {
    m_mutex.lock();
    assert(m_gameobjects.find(object->getID()) != m_gameobjects.end());
    if (m_gameobjects.find(object->getID()) != m_gameobjects.end()) {
        object->removeSelfFromSystems();
        m_gameobjects.erase(object->getID());
    }
    m_mutex.unlock();
}

void GameWorld::removeGameObject(std::string id) {
    // there shouldn't be a mutex here
    assert(m_gameobjects.find(id) != m_gameobjects.end());
    if (m_gameobjects.find(id) != m_gameobjects.end()) {
        m_gameobjects[id]->removeSelfFromSystems();
        m_gameobjects.erase(m_gameobjects[id]->getID());
    }
}

void GameWorld::onKeyPressed(QKeyEvent *event) {
    m_mutex.lock();
    getSystem<ControlCallbackSystem>()->onKeyPressed(event);
    m_mutex.unlock();
}

void GameWorld::markGameObjectForDeletion(std::string id) {
    m_mutex.lock();
    ids_to_delete.insert(id);
    m_mutex.unlock();
}

void GameWorld::removeGameObjectsMarkedForDeletion() {
    m_mutex.lock();
    for (auto it = ids_to_delete.begin(); it != ids_to_delete.end(); it++) {
        removeGameObject(*it);
    }
    ids_to_delete.clear();
    m_mutex.unlock();
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
    m_mutex.lock();
    m_uis[name] = ui;
    ui->setGameWorld(this);
    m_mutex.unlock();
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
    m_mutex.lock();
    assert(m_gameobjects.find(id) != m_gameobjects.end());
    std::shared_ptr<GameObject> ret = m_gameobjects[id];
    m_mutex.unlock();
    return ret;
}

bool GameWorld::checkIfGameObjectExists(std::string id) {
    return m_gameobjects.find(id) != m_gameobjects.end();
}
