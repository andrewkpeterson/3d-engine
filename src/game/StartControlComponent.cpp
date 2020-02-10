#include "StartControlComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/Screen.h"
#include "src/engine/common/Application.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/system/ControlCallbackSystem.h"

StartControlComponent::StartControlComponent(GameObject *gameobject) :
    ControlCallbackComponent (gameobject)
{

}

void StartControlComponent::addComponentToSystems()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->addComponent(this);
}

void StartControlComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->removeComponent(this);
}

StartControlComponent::~StartControlComponent()
{

}

void StartControlComponent::onMousePressed(QMouseEvent *event) {
    m_gameobject->getGameWorld()->getScreen()->getApp()->changeScreen("gameplay");
}
