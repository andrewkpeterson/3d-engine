#include "DungeonPauseControlComponent.h"
#include "src/engine/common/Application.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/system/ControlCallbackSystem.h"

DungeonPauseControlComponent::DungeonPauseControlComponent() :
    ControlCallbackComponent()

{

}

DungeonPauseControlComponent::~DungeonPauseControlComponent()
{

}

void DungeonPauseControlComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->addComponent(this);

}

void DungeonPauseControlComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->removeComponent(this);
}


void DungeonPauseControlComponent::tick(float seconds) {
}




void DungeonPauseControlComponent::onMouseDragged(int deltaX, int deltaY) {

}

void DungeonPauseControlComponent::onKeyPressed(QKeyEvent *event) {
    if (event->key() == Qt::Key_P) m_gameobject->getGameWorld()->getScreen()->getApp()->changeScreen("gameplay");
}

void DungeonPauseControlComponent::onKeyReleased(QKeyEvent *event) {
}

void DungeonPauseControlComponent::onKeyRepeated(QKeyEvent *event) {
}

void DungeonPauseControlComponent::onMousePressed(QMouseEvent *event) {
}

void DungeonPauseControlComponent::onMouseReleased(QMouseEvent *event) {

}

void DungeonPauseControlComponent::onWheelEvent(QWheelEvent *event) {

}
