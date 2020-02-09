#include "PlayerControlComponent.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/system/ControlCallbackSystem.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/util/Input.h"

PlayerControlComponent::PlayerControlComponent(std::shared_ptr<GameObject> gameobject) :
    ControlCallbackComponent(gameobject),
    off_ground(false),
    y_vel(0.0)
{

}

PlayerControlComponent::~PlayerControlComponent()
{

}

void PlayerControlComponent::addGameObjectToSystems()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->addComponent(this);
}

void PlayerControlComponent::removeGameObjectFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->removeComponent(this);
}

void PlayerControlComponent::draw(Graphics *g) {
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    g->setCamera(camera);
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

void PlayerControlComponent::tick(float seconds) {
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    glm::vec3 look = camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

    if (Input::getPressed("W")) camera->translate(dir * WALK_SPEED);
    if (Input::getPressed("S")) camera->translate(-dir * WALK_SPEED);
    if (Input::getPressed("A")) camera->translate(perp * WALK_SPEED);
    if (Input::getPressed("D")) camera->translate(-perp * WALK_SPEED);

    if (Input::getPressed("R")) {
        m_gameobject->getGameWorld()->getScreen()->restartApplication();
    }

    // handle jumping
    if (Input::getPressed("SPACE") && !off_ground) {
        std::cout << "jumped" << std::endl;
        off_ground = true;
        y_vel = JUMP_SPEED;
    }

    // handle falling back to ground
    if (camera->getEye().y < 1) {
        std::cout << "hit ground" << std::endl;
        off_ground = false;
        y_vel = 0;
        camera->setEye(glm::vec3(camera->getEye().x, 1.0f, camera->getEye().z));
    }

    // handle chaning y value
    camera->setEye(glm::vec3(camera->getEye().x, camera->getEye().y + y_vel, camera->getEye().z));
    if (off_ground) {
        y_vel += GRAVITY * seconds;
    }
}


void PlayerControlComponent::onMouseDragged(int deltaX, int deltaY) {
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    camera->rotate(-deltaX / 100.0f * MOUSE_SENSITIVITY, -deltaY / 100.0f * MOUSE_SENSITIVITY);
}

void PlayerControlComponent::onKeyPressed(QKeyEvent *event) {
}

void PlayerControlComponent::onKeyReleased(QKeyEvent *event) {
}

void PlayerControlComponent::onKeyRepeated(QKeyEvent *event) {
}

void PlayerControlComponent::onMousePressed(QMouseEvent *event) {
}

void PlayerControlComponent::onMouseReleased(QMouseEvent *event) {
}

void PlayerControlComponent::onWheelEvent(QWheelEvent *event) {
}
