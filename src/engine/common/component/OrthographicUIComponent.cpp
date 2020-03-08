#include "OrthographicUIComponent.h"
#include "src/engine/graphics/Camera.h"
#include "TransformComponent.h"
#include "src/engine/common/system/OrthographicUISystem.h"

OrthographicUIComponent::OrthographicUIComponent(std::string matname, Material material, glm::vec3 offset) :
    DrawableComponent(),
    m_offset(offset),
    m_matname(matname)
{
    g = Graphics::getGlobalInstance();
    g->addMaterial(m_matname, material);
}

OrthographicUIComponent::OrthographicUIComponent(std::string matname, glm::vec3 offset) :
    DrawableComponent(),
    m_offset(offset),
    m_matname(matname)
{
    g = Graphics::getGlobalInstance();
}

OrthographicUIComponent::~OrthographicUIComponent()
{

}

void OrthographicUIComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<OrthographicUISystem>()->addComponent(this);
}

void OrthographicUIComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<OrthographicUISystem>()->removeComponent(this);
}

glm::vec3 OrthographicUIComponent::convertToScreenSpace(glm::vec3 pos, std::shared_ptr<Camera> camera) {
    glm::vec4 pos_clip_space = camera->getProjection() * camera->getView() * glm::vec4(pos, 1.0f);
    glm::vec2 screen_size = camera->getScreenSize();
    glm::vec3 pos_ndc = glm::vec3(pos_clip_space.x / pos_clip_space.w, pos_clip_space.y / pos_clip_space.w, pos_clip_space.z / pos_clip_space.w);
    return glm::vec3((pos_ndc.x + 1) * .5f * screen_size.x,
                     (pos_ndc.y + 1) * .5f * screen_size.y, pos_ndc.z);
}
