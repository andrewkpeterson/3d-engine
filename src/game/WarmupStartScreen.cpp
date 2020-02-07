#include "WarmupStartScreen.h"
#include "src/engine/util/Input.h"

WarmupStartScreen::WarmupStartScreen(Graphics *g, WarmupApplication *parent_app) :
    Screen(parent_app)
{
    m_camera = std::make_shared<Camera>();
    m_camera->setUI(true);
    Material whiteMaterial;
    whiteMaterial.color = glm::vec3(1, 1, 1);
    g->addMaterial("white", whiteMaterial);
}

WarmupStartScreen::~WarmupStartScreen()
{

}

void WarmupStartScreen::draw(Graphics *g) {
    g->setCamera(m_camera);

    g->clearTransform();
    g->setMaterial("white");
    g->translate(glm::vec3(20.0f, 20.0f, 0.0f));
    g->drawText("Press mouse to play", 80);
}

void WarmupStartScreen::tick(float seconds) {
    if (Input::getPressed("MOUSE")) {
        m_parent->changeScreen("gameplay");
    }
}

void WarmupStartScreen::restartScreen() {
    Screen::restartScreen();
}


void WarmupStartScreen::onMousePressed(QMouseEvent *event) {
    m_parent->changeScreen("gameplay");
}

void WarmupStartScreen::resize(int w, int h) {
    m_camera->setScreenSize(glm::vec2(w,h));
}
