#include "CameraComponent.h"
#include "src/engine/common/system/CameraSystem"

CameraComponent::CameraComponent(std::shared_ptr<GameObject> gameobject) :
    Component("CameraComponent", gameobject)
{

}

CameraComponent::~CameraComponent()
{

}

void DrawableComponent::addGameObjectToSystems()
{
    m_gameobject->getGameWorld()->getSystem<CameraSystem>()->addGameObject(m_gameobject);
}

void DrawableComponent::removeGameObjectFromSystems() {
    m_gameobject->getGameWorld()->getSystem<CameraSystem>()->removeGameObject(m_gameobject);
}
