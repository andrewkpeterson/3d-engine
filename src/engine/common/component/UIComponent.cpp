#include "UIComponent.h"

#include "src/engine/common/ui/UILabel.h"
#include "src/engine/common/ui/UIElement.h"
#include "src/engine/graphics/Camera.h"
#include "src/engine/common/system/UISystem.h"

UIComponent::UIComponent() :
    Component(),
    m_camera(std::make_shared<Camera>()),
    should_display(true)
{
    g = Graphics::getGlobalInstance();
    m_camera->setUI(true);
}

UIComponent::~UIComponent()
{

}

void UIComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<UISystem>()->addComponent(this);
}

void UIComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<UISystem>()->removeComponent(this);
}

std::shared_ptr<UIElement> UIComponent::getElement(std::string name) {
    return m_elements[name];
}

void UIComponent::addElement(std::string name, std::shared_ptr<UIElement> elt) {
    m_elements[name] = elt;
}

void UIComponent::resize(int width, int height) {
    m_camera->setScreenSize(glm::vec2(width, height));
}

void UIComponent::setGameWorld(GameWorld *gameworld) {
    m_gameworld = gameworld;
}

void UIComponent::setShouldDisplay(bool b) {
    should_display = b;
}

void UIComponent::drawSelf() {
    if (should_display) {
        for (auto it = m_elements.begin(); it != m_elements.end(); it++) {
            std::shared_ptr<UIElement> elt = it->second;
            elt->drawSelf();
        }
    }
}

void UIComponent::tick(float seconds) {
    for (auto it = m_elements.begin(); it != m_elements.end(); it++) {
        std::shared_ptr<UIElement> elt = it->second;
        elt->tick(seconds);
    }
}
