#include "UIControllerComponent.h"
#include "src/engine/common/Application.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/system/ControlCallbackSystem.h"
#include "TransformComponent.h"

UIControllerComponent::UIControllerComponent(std::string cursor_geometry, std::string cursor_matname, glm::vec3 cursor_size) :
    ControlCallbackComponent(),
    m_cursor_geometry(cursor_geometry),
    m_cursor_matname(cursor_matname),
    m_mouse_pressed(false),
    m_cursor_size(cursor_size)
{
    g = Graphics::getGlobalInstance();
}

UIControllerComponent::~UIControllerComponent()
{

}

void UIControllerComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->addComponent(this);

}

void UIControllerComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->removeComponent(this);
}


void UIControllerComponent::tick(float seconds) {
}

void UIControllerComponent::drawCursor() {
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    g->clearTransform();
    g->setMaterial(m_cursor_matname);
    g->translate(glm::vec3(t->getPos().x, t->getPos().y, 0.0f)); // this is the only necessary world transform
    t->setObjectSpaceOrientation();
    g->scale(glm::vec3(m_cursor_size.x,m_cursor_size.y,1.0));
    g->drawShape(m_cursor_geometry);
}

void UIControllerComponent::onMouseDragged(int deltaX, int deltaY) {
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    t->translate(glm::vec3(deltaX, -deltaY,0));
    glm::vec2 screen_size = m_gameobject->getGameWorld()->getScreen()->getApp()->getScreenSize();
    float x = glm::clamp(t->getPos().x, 0.0f, screen_size.x);
    float y = glm::clamp(t->getPos().y, 0.0f, screen_size.y);
    t->setPos(glm::vec3(x, y, 0));
}

void UIControllerComponent::onKeyPressed(QKeyEvent *event) {

}

void UIControllerComponent::onKeyReleased(QKeyEvent *event) {

}

void UIControllerComponent::onKeyRepeated(QKeyEvent *event) {

}

void UIControllerComponent::onMousePressed(QMouseEvent *event) {
}

void UIControllerComponent::onMouseReleased(QMouseEvent *event) {

}

void UIControllerComponent::onWheelEvent(QWheelEvent *event) {

}
