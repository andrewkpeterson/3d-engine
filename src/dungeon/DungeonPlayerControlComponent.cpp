#include "DungeonPlayerControlComponent.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/system/ControlCallbackSystem.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/CylinderCollisionComponent.h"
#include "src/engine/common/component/DynamicAABCollisionComponent.h"
#include "src/engine/common/ui/UI.h"
#include "src/engine/util/Input.h"

DungeonPlayerControlComponent::DungeonPlayerControlComponent() :
    ControlCallbackComponent(),
    off_ground(false),
    can_jump(true),
    y_vel(0.0),
    distance_last_fallen(0),
    use_third_person(true),
    third_person_cam_pos(5.0),
    m_deltaX(0),
    m_deltaY(0)
{

}

DungeonPlayerControlComponent::~DungeonPlayerControlComponent()
{

}

void DungeonPlayerControlComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->addComponent(this);

    m_gameobject->getComponent<DynamicAABCollisionComponent>()->
            setCollisionCallback(std::bind(&DungeonPlayerControlComponent::handleCollisionResolutionAndResponse, this, std::placeholders::_1));
}

void DungeonPlayerControlComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->removeComponent(this);
}


void DungeonPlayerControlComponent::tick(float seconds) {
    update(seconds);
}

void DungeonPlayerControlComponent::handleCollisionResolutionAndResponse(Collision collision) {
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    std::shared_ptr<DynamicAABCollisionComponent> comp = m_gameobject->getComponent<DynamicAABCollisionComponent>();
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    glm::vec3 look = camera->getLook();
    //if (collision.half_mtv.x == 0 && collision.half_mtv.z == 0 && collision.half_mtv.y > 0 && y_vel < 0) {
        //can_jump = true;
        //t->translate(glm::vec3(0,distance_last_fallen,0));
    //} else {
        if (collision.collider->canMove()) {
            t->translate(collision.half_mtv);
        } else {
            t->translate(2.0f*collision.half_mtv);
        }
        if (use_third_person) {
            camera->setEye(t->getPos() + glm::vec3(0,1,0) - third_person_cam_pos*look);
        } else {
            camera->setEye(t->getPos() + glm::vec3(0,1,0));
        }
    //}
}

void DungeonPlayerControlComponent::update(float seconds) {
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    glm::vec3 look = camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    if (Input::getPressed("W")) {
        t->translate(dir * WALK_SPEED);
    }
    if (Input::getPressed("S")) {
        t->translate(-dir * WALK_SPEED);
    }
    if (Input::getPressed("A")) {
        t->translate(perp * WALK_SPEED);
    }
    if (Input::getPressed("D")) {
        t->translate(-perp * WALK_SPEED);
    }

    /*
    // handle jumping
    if (Input::getPressed("SPACE") && can_jump) {
        off_ground = true;
        can_jump = false;
        y_vel = JUMP_SPEED;
    }

    // handle falling back to ground
    if (t->getPos().y < GROUND_LEVEL) {
        off_ground = false;
        can_jump = true;
        y_vel = 0;
        t->setPos(glm::vec3(t->getPos().x, GROUND_LEVEL, t->getPos().z));
        distance_last_fallen = 0;
    }

    // handle changing y value
    t->setPos(glm::vec3(t->getPos().x, t->getPos().y + y_vel * seconds, t->getPos().z));
    distance_last_fallen = 0;
    if (!can_jump) {
        y_vel += GRAVITY * seconds;
        t->setPos(glm::vec3(t->getPos().x, t->getPos().y + y_vel * seconds, t->getPos().z));
        distance_last_fallen = y_vel * seconds;
    }
    */

    //set the camera eye to the appropriate place given the position of the transformation component
    if (use_third_person) {
        camera->setEye(t->getPos() + glm::vec3(0,1,0) - third_person_cam_pos*look);
    } else {
        camera->setEye(t->getPos() + glm::vec3(0,1,0));
    }

    //camera->rotate(-m_deltaX / 100.0f * MOUSE_SENSITIVITY * seconds, -m_deltaY / 100.0f * MOUSE_SENSITIVITY * seconds);
}


void DungeonPlayerControlComponent::onMouseDragged(int deltaX, int deltaY) {
    m_deltaX = deltaX;
    m_deltaY = deltaY;
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    camera->rotate(-m_deltaX / 100.0f * MOUSE_SENSITIVITY, -m_deltaY / 100.0f * MOUSE_SENSITIVITY);
}

void DungeonPlayerControlComponent::onKeyPressed(QKeyEvent *event) {
    if (event->key() == Qt::Key_R) m_gameobject->getGameWorld()->getScreen()->setAppReadyToRestart();
    if (event->key() == Qt::Key_T) {
        use_third_person = !use_third_person;
        m_gameobject->getComponent<PrimitiveDrawableComponent>()->setDraw(use_third_person);
    }
}

void DungeonPlayerControlComponent::onKeyReleased(QKeyEvent *event) {
}

void DungeonPlayerControlComponent::onKeyRepeated(QKeyEvent *event) {
}

void DungeonPlayerControlComponent::onMousePressed(QMouseEvent *event) {
}

void DungeonPlayerControlComponent::onMouseReleased(QMouseEvent *event) {
}

void DungeonPlayerControlComponent::onWheelEvent(QWheelEvent *event) {
    if (use_third_person) {
        third_person_cam_pos = glm::clamp(third_person_cam_pos - .002f*event->angleDelta().y(),
                                          MIN_CAM_TRANSLATION, MAX_CAM_TRANSLATION);
    }
}
