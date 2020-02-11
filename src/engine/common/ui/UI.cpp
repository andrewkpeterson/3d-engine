#include "UI.h"

#include "UIElement.h"
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
        for (int i = 0; i < m_elements.size(); i++) {
            m_elements[i]->drawSelf();
        }
    }
}

void UI::addElement(std::shared_ptr<UIElement> elt) {
    m_elements.push_back(elt);
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
