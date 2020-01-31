#include "WarmupGameplayScreen.h"

WarmupGameplayScreen::WarmupGameplayScreen(Graphics *g) :
    Screen()
{
    m_camera = std::make_shared<Camera>();
    m_camera->setEye(glm::vec3(0,1,0));
    g->setCamera(m_camera);

    Material myFirstMaterial;
    myFirstMaterial.color = glm::vec3(0, 1, 0);
    g->addMaterial("boringGreen", myFirstMaterial);

    Material mySecondMaterial;
    mySecondMaterial.textureName = "grass";
    g->addMaterial("grassMaterial", mySecondMaterial);
}

WarmupGameplayScreen::~WarmupGameplayScreen()
{

}

void WarmupGameplayScreen::draw(Graphics *g) {
    g->clearTransform();
    g->scale(20.0);
    g->setMaterial("grassMaterial");
    g->drawShape("quad");

    g->clearTransform();
    g->setDefaultMaterial();
    g->translate(glm::vec3(1.0f, 1.0f, 10.0f));
    g->scale(5);
    g->drawShape("cylinder");
}

void WarmupGameplayScreen::tick(float seconds) {
    glm::vec3 look = m_camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

    if (m_controlstates["W"]) m_camera->translate(dir * WALK_SPEED);
    if (m_controlstates["S"]) m_camera->translate(-dir * WALK_SPEED);
    if (m_controlstates["A"]) m_camera->translate(perp * WALK_SPEED);
    if (m_controlstates["D"]) m_camera->translate(-perp * WALK_SPEED);
}


void WarmupGameplayScreen::onMouseDragged(int deltaX, int deltaY) {
    m_camera->rotate(-deltaX / 100.0f * MOUSE_SENSITIVITY, -deltaY / 100.0f * MOUSE_SENSITIVITY);
}


void WarmupGameplayScreen::restart() {

}

void WarmupGameplayScreen::resize(int w, int h) {
    m_camera->setScreenSize(glm::vec2(w, h));
}


