#include "UI.h"

#include "UIElement.h"
#include "UILabel.h"
#include "src/engine/graphics/Camera.h"

UI::UI() :
    m_camera(std::make_shared<Camera>()),
    should_display(true)
{
    g = Graphics::getGlobalInstance();
    m_camera->setUI(true);
}

UI::~UI()
{

}

void UI::drawUI() {
    if (should_display) {
        g->setCamera(m_camera);
        auto it = m_elements.begin();
        while (it != m_elements.end()) {
            it->second->drawSelf();
            it++;
        }
    }
}

std::shared_ptr<UILabel> UI::getLabel(std::string name) {
    return m_elements[name];
}

void UI::addElement(std::string name, std::shared_ptr<UILabel> elt) {
    m_elements[name] = elt;
}

void UI::resize(int width, int height) {
    m_camera->setScreenSize(glm::vec2(width, height));
}

void UI::setGameWorld(GameWorld *gameworld) {
    m_gameworld = gameworld;
}

void UI::setShouldDisplay(bool b) {
    should_display = b;
}
