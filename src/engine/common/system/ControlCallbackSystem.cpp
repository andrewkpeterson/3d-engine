#include "ControlCallbackSystem.h"
#include "src/engine/common/GameObject.h"

ControlCallbackSystem::ControlCallbackSystem(std::shared_ptr<GameWorld> gameworld) :
    System("ControlCallbackSystem", gameworld)
{

}

ControlCallbackSystem::~ControlCallbackSystem()
{

}

void ControlCallbackSystem::addComponent(ControlCallbackComponent *component) {
    m_components.insert(component);
}

void ControlCallbackSystem::removeComponent(ControlCallbackComponent *component) {
    m_components.erase(component);
}

void ControlCallbackSystem::onKeyPressed(QKeyEvent *event) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        ControlCallbackComponent *comp = *it;
        comp->onKeyPressed(event);
        it++;
    }
}

void ControlCallbackSystem::onKeyReleased(QKeyEvent *event) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        ControlCallbackComponent *comp = *it;
        comp->onKeyReleased(event);
        it++;
    }
}

void ControlCallbackSystem::onKeyRepeated(QKeyEvent *event) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        ControlCallbackComponent *comp = *it;
        comp->onKeyRepeated(event);
        it++;
    }
}

void ControlCallbackSystem::onMousePressed(QMouseEvent *event) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        ControlCallbackComponent *comp = *it;
        comp->onMousePressed(event);
        it++;
    }
}

void ControlCallbackSystem::onMouseReleased(QMouseEvent *event) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        ControlCallbackComponent *comp = *it;
        comp->onMouseReleased(event);
        it++;
    }
}

void ControlCallbackSystem::onMouseDragged(int deltaX, int deltaY) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        ControlCallbackComponent *comp = *it;
        comp->onMouseDragged(deltaX, deltaY);
        it++;
    }
}

void ControlCallbackSystem::onWheelEvent(QWheelEvent *event) {
    auto it = m_components.begin();
    while(it != m_components.end()) {
        ControlCallbackComponent *comp = *it;
        comp->onWheelEvent(event);
        it++;
    }
}
