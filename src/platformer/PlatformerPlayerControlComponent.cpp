#include "PlatformerPlayerControlComponent.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/system/ControlCallbackSystem.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/CylinderCollisionComponent.h"
#include "src/engine/common/component/DynamicAABCollisionComponent.h"
#include "src/engine/common/ui/UI.h"
#include "src/engine/common/ui/UILabel.h"
#include "src/dungeon/SwordComponent.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/Application.h"
#include "src/engine/common/Screen.h"
#include "src/engine/common/component/EllipsoidComponent.h"
#include <sstream>
#include <iostream>

PlatformerPlayerControlComponent::PlatformerPlayerControlComponent() :
    ControlCallbackComponent(),
    on_ground(false),
    can_jump(false),
    last_normal(0,1,0),
    y_vel(0.0),
    distance_last_fallen(0),
    use_third_person(false),
    third_person_cam_pos(5.0),
    m_deltaX(0),
    m_deltaY(0)
{

}

PlatformerPlayerControlComponent::~PlatformerPlayerControlComponent()
{

}

void PlatformerPlayerControlComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->addComponent(this);

    /*
    m_gameobject->getComponent<DynamicAABCollisionComponent>()->
            setCollisionCallback(std::bind(&DungeonPlayerControlComponent::handleCollisionResolutionAndResponse,
                                           this, std::placeholders::_1));
    */
    m_gameobject->getComponent<PrimitiveDrawableComponent>()->setDraw(use_third_person);
}

void PlatformerPlayerControlComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->removeComponent(this);
}


void PlatformerPlayerControlComponent::tick(float seconds) {
    update(seconds);
}

/*
void PlatformerPlayerControlComponent::handleCollisionResolutionAndResponse(Collision collision) {
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    std::shared_ptr<DynamicAABCollisionComponent> comp = m_gameobject->getComponent<DynamicAABCollisionComponent>();
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    glm::vec3 look = camera->getLook();
    std::string id = collision.collider->getGameObject()->getID();
    //if (collision.half_mtv.x == 0 && collision.half_mtv.z == 0 && collision.half_mtv.y > 0 && y_vel < 0) {
        //can_jump = true;
        //t->translate(glm::vec3(0,distance_last_fallen,0));
    //} else {
    if (id.find("sword") == std::string::npos) {
        if (collision.collider->canMove()) {
            t->translate(collision.half_mtv);
        } else {
            t->translate(2.0f*collision.half_mtv);
        }
        if (use_third_person) {
            camera->setEye(t->getPos() + glm::vec3(0,3,0) - third_person_cam_pos*look);
        } else {
            camera->setEye(t->getPos() + glm::vec3(0,3,0));
        }
    }
    //}
}
*/

void PlatformerPlayerControlComponent::update(float seconds) {
    glm::vec3 old_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    glm::vec3 look = camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

    bool moving_laterally = false;
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    if (Input::getPressed("W")) {
        t->translate(dir * WALK_SPEED);
        moving_laterally = true;
    }
    if (Input::getPressed("S")) {
        t->translate(-dir * WALK_SPEED);
        moving_laterally = true;
    }
    if (Input::getPressed("A")) {
        t->translate(perp * WALK_SPEED);
        moving_laterally = true;
    }
    if (Input::getPressed("D")) {
        t->translate(-perp * WALK_SPEED);
        moving_laterally = true;
    }

    //set the camera eye to the appropriate place given the position of the transformation component
    glm::vec3 pos_due_to_gravity;
    if (!on_ground) {
        y_vel += GRAVITY * seconds;
        t->setPos(glm::vec3(t->getPos().x, t->getPos().y + y_vel * seconds, t->getPos().z));
        //std::cout << "yes" << std::endl;
    } else {
        y_vel = 0;
        //std::cout << "no" << std::endl;
    }
    if (Input::getPressed("SPACE") && on_ground) {
        on_ground = false;
        y_vel = JUMP_SPEED;
    }

    std::pair<std::vector<EllipsoidTriangleCollision>, glm::vec3> p =
            m_gameobject->getComponent<EllipsoidComponent>()->checkCollisionAndTranslate(old_pos, t->getPos());
    glm::vec3 norm = glm::vec3(0,0,0);
    bool had_collision = p.first.size() > 0;
    if (had_collision) {
        frames_since_last_collision = 0;
        norm = p.first[0].normal;
        last_normal = norm;
        //std::cout << "collision" << std::endl;
    } else {
        //std::cout << "no collision" << std::endl;
        frames_since_last_collision++;

    }


    if (!moving_laterally && glm::dot(glm::vec3(0,1,0), norm) > 0) {
        // if we don't move laterally, then if the translation is small, we don't need to move at all
        t->setPos(old_pos);
    } else if (moving_laterally && glm::dot(glm::vec3(0,1,0), last_normal) > .99 && frames_since_last_collision < 5) {
        // if we move laterally and we are on flat ground, then the the height is kept constant
        //t->setPos(glm::vec3(t->getPos().x, old_pos.y, t->getPos().z));
        //std::cout << "hello" << std::endl;
    }
    on_ground = glm::dot(glm::vec3(0,1,0), norm) > 0;

    heights.push_back(t->getPos().y);
    if (heights.size() > 5) {
        heights.erase(heights.begin());
    }

    if (moving_laterally && norm.y < .001) {
        //t->setPos(glm::vec3(t->getPos().x, old_pos.y + y_vel * seconds, t->getPos().z));
    }

    // when we are on a ramp, we can manually increase the speed
    if (0 < norm.y && norm.y < 1 && frames_since_last_collision < 5 && moving_laterally) {
        t->translate(glm::vec3(0,.1,0));
    }

    // if we are jumping and running towards a wall, make sure we don't stick to the wall
    if (false) {
        //t->translate(.05f*norm);
    }

    // if we are moving laterally and against a wall, make sure we don't stick to the wall
    if (false) {
        //t->translate(.05f*norm);
    }


    if (use_third_person) {
        camera->setEye(t->getPos() + glm::vec3(0,3,0) - third_person_cam_pos*look);
    } else {
        camera->setEye(t->getPos() + glm::vec3(0,3,0));
    }
}


void PlatformerPlayerControlComponent::onMouseDragged(int deltaX, int deltaY) {
    m_deltaX = deltaX;
    m_deltaY = deltaY;
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    camera->rotate(-m_deltaX / 100.0f * MOUSE_SENSITIVITY, -m_deltaY / 100.0f * MOUSE_SENSITIVITY);
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    t->changeYaw(-m_deltaX / 100.0f * MOUSE_SENSITIVITY);
}

void PlatformerPlayerControlComponent::onKeyPressed(QKeyEvent *event) {
    if (event->key() == Qt::Key_R) m_gameobject->getGameWorld()->getScreen()->setAppReadyToRestart();
    if (event->key() == Qt::Key_T) {
        use_third_person = !use_third_person;
        m_gameobject->getComponent<PrimitiveDrawableComponent>()->setDraw(use_third_person);
    }
    if (event->key() == Qt::Key_P) m_gameobject->getGameWorld()->getScreen()->getApp()->changeScreen("pause");
}

void PlatformerPlayerControlComponent::onKeyReleased(QKeyEvent *event) {
}

void PlatformerPlayerControlComponent::onKeyRepeated(QKeyEvent *event) {
}

void PlatformerPlayerControlComponent::onMousePressed(QMouseEvent *event) {

}

void PlatformerPlayerControlComponent::onMouseReleased(QMouseEvent *event) {
}

void PlatformerPlayerControlComponent::onWheelEvent(QWheelEvent *event) {
    if (use_third_person) {
        third_person_cam_pos = glm::clamp(third_person_cam_pos - .002f*event->angleDelta().y(),
                                          MIN_CAM_TRANSLATION, MAX_CAM_TRANSLATION);
    }
}
