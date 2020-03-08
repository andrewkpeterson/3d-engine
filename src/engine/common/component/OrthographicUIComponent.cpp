#include "OrthographicUIComponent.h"
#include "src/engine/graphics/Camera.h"
#include "TransformComponent.h"
#include "src/engine/common/system/OrthographicUISystem.h"

OrthographicUIComponent::OrthographicUIComponent(std::string geometry, std::string matname, Material material) :
    DrawableComponent(),
    m_matname(matname),
    m_geometry(geometry),
    m_camera(std::make_shared<Camera>())
{
    g = Graphics::getGlobalInstance();
    g->addMaterial(m_matname, material);
    m_camera->setUI(true);
}

OrthographicUIComponent::OrthographicUIComponent(std::string geometry, std::string matname) :
    DrawableComponent(),
    m_matname(matname),
    m_geometry(geometry),
    m_camera(std::make_shared<Camera>())
{
    g = Graphics::getGlobalInstance();
    m_camera->setUI(true);
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

void OrthographicUIComponent::drawSelf(std::shared_ptr<Camera> camera) {
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    glm::vec3 screen_pos = convertToScreenSpace(t->getPos() + glm::vec3(0,4.0,0), camera);
    if (screen_pos.z > 0) {
        if (shouldDraw) {
            g->clearTransform();
            g->setMaterial("health_bar_mat");
            g->translate(glm::vec3(screen_pos.x, screen_pos.y, screen_pos.z));
            g->scale(glm::vec3(50,10,1));
            g->drawShape(m_geometry);
        }
    }
}

glm::vec3 OrthographicUIComponent::convertToScreenSpace(glm::vec3 pos, std::shared_ptr<Camera> camera) {
    glm::vec4 pos_clip_space = camera->getProjection() * camera->getView() * glm::vec4(pos, 1.0f);
    glm::vec2 screen_size = camera->getScreenSize();
    glm::vec3 pos_ndc = glm::vec3(pos_clip_space.x / pos_clip_space.w, pos_clip_space.y / pos_clip_space.w, pos_clip_space.z / pos_clip_space.w);
    return glm::vec3((pos_ndc.x + 1) * .5f * screen_size.x,
                     (pos_ndc.y + 1) * .5f * screen_size.y, pos_ndc.z);
}
