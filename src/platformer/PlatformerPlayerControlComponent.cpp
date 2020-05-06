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
#include "src/engine/common/system/UISystem.h"
#include "src/engine/common/component/UIComponent.h"
#include "src/dungeon/SwordComponent.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/Application.h"
#include "src/engine/common/Screen.h"
#include "src/engine/common/component/EllipsoidComponent.h"
#include "src/platformer/PlatformerPlayerBulletControllerComponent.h"
#include "src/platformer/prefabs/PlayerBullet.h"
#include "src/engine/common/component/SoundComponent.h"
#include "src/engine/common/animation/AnimatedModelComponent.h"
#include <sstream>
#include <iostream>

PlatformerPlayerControlComponent::PlatformerPlayerControlComponent()
    : ControlCallbackComponent(), on_ground(false), can_jump(false), last_normal(0, 1, 0),
      y_vel(0.0), distance_last_fallen(0), use_third_person(true), third_person_cam_pos(5.0),
      m_deltaX(0), m_deltaY(0), saved_laser_time(0), dodging(false), dodge_recharging(false),
      saved_dodge_time(0), saved_dodge_recharge_time(0), jump_queued(false), jump_anim_time(0),
      falling(false), health_bar(3), recovering(false), saved_recover_time(0), saved_invincible_time(0),
      invincible(false), invincible_flicker_time(0), game_over(false), down_time(0), starting(true)
{

}

PlatformerPlayerControlComponent::~PlatformerPlayerControlComponent()
{

}

void PlatformerPlayerControlComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->addComponent(this);

    m_gameobject->getComponent<SphereCollisionComponent>()->
            setCollisionCallback(std::bind(&PlatformerPlayerControlComponent::handleCollisionResolutionAndResponse,
                                           this, std::placeholders::_1));
    //m_gameobject->getComponent<PrimitiveDrawableComponent>()->setDraw(use_third_person);
}

void PlatformerPlayerControlComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
    m_gameobject->getGameWorld()->getSystem<ControlCallbackSystem>()->removeComponent(this);
}


void PlatformerPlayerControlComponent::tick(float seconds) {
    updateMovement(seconds);
    shoot(seconds);
    setPositionOfCamera();
    updateDodge(seconds);
}

void PlatformerPlayerControlComponent::updateDodge(float seconds) {
    if (dodging) {
        saved_dodge_time += seconds;
        //std::cout << "dodge" << std::endl;
    } else {
        saved_dodge_recharge_time += seconds;
        //std::cout << "not dodge" << std::endl;
    }
    if (saved_dodge_time > TOTAL_DODGE_TIME) {
        saved_dodge_time = 0;
        dodging = false;
    }
}


void PlatformerPlayerControlComponent::handleCollisionResolutionAndResponse(Collision collision) {
    if (!invincible && !recovering) {
        std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
        std::shared_ptr<SphereCollisionComponent> comp = m_gameobject->getComponent<SphereCollisionComponent>();
        std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
        glm::vec3 look = camera->getLook();
        std::string id = collision.collider->getGameObject()->getID();
        std::cout << "hit" << std::endl;
        std::shared_ptr<AnimatedModelComponent> anim_comp = m_gameobject->getComponent<AnimatedModelComponent>();
        recovering = true;
        health_bar -= 1;
        if (health_bar == 2)
            m_gameobject->getGameWorld()->getGameObjectByID("HUD")->getComponent<UIComponent>()->getElement("health_bar3")->setDraw(false);
        else if (health_bar == 1)
            m_gameobject->getGameWorld()->getGameObjectByID("HUD")->getComponent<UIComponent>()->getElement("health_bar2")->setDraw(false);
        else if (health_bar == 0)
            m_gameobject->getGameWorld()->getGameObjectByID("HUD")->getComponent<UIComponent>()->getElement("health_bar1")->setDraw(false);
        if (health_bar > 0) {
            recovering = true;
            anim_comp->setAnimation("damaged");
        } else {
            anim_comp->setAnimation("died");
            game_over = true;
        }
    }
}


void PlatformerPlayerControlComponent::updateMovement(float seconds) {
    if (starting) {
        seconds = .02;
        starting = false;
    }
    glm::vec3 old_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
    std::shared_ptr<AnimatedModelComponent> anim_comp = m_gameobject->getComponent<AnimatedModelComponent>();
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    if (game_over) {
        down_time += seconds;
        if (down_time > TOTAL_DOWN_TIME) {
            anim_comp->setAnimation("down");
            if (Input::getPressed("SPACE")) {
                m_gameobject->getGameWorld()->getScreen()->getApp()->setReadyToRestart();
            }
            m_gameobject->getGameWorld()->getGameObjectByID("game_over")->getComponent<UIComponent>()->getElement("title")->setDraw(true);
            m_gameobject->getGameWorld()->getGameObjectByID("game_over")->getComponent<UIComponent>()->getElement("directions")->setDraw(true);

        }
        y_vel += GRAVITY * seconds;
        t->setPos(glm::vec3(t->getPos().x, t->getPos().y + y_vel * seconds, t->getPos().z));

        // ********************************************************************
        // if we are on the ground, set y_vel to 0
        if (on_ground) {
            if (y_vel < 0) {
                y_vel = 0;
            }
        }

        std::pair<std::vector<EllipsoidTriangleCollision>, glm::vec3> p =
            m_gameobject->getComponent<EllipsoidComponent>()->checkCollisionAndTranslate(old_pos, t->getPos(), true);

        on_ground = false;
        for (int i = 0; i < p.first.size(); i++) {
            if (glm::dot(glm::vec3(0,1,0), p.first[i].normal) > 0) {
                on_ground = true;
                falling = false;
            }
        }

        if (on_ground) {
            t->setPos(old_pos);
        }

        return;
    }

    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    glm::vec3 look = camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

    if (recovering) {
        saved_recover_time += seconds;
        if (saved_recover_time > TOTAL_RECOVER_TIME) {
            anim_comp->setAnimation("rest");
            recovering = false;
            saved_recover_time = 0;
            invincible = true;
        }

        y_vel += GRAVITY * seconds;
        t->setPos(glm::vec3(t->getPos().x, t->getPos().y + y_vel * seconds, t->getPos().z));

        // ********************************************************************
        // if we are on the ground, set y_vel to 0
        if (on_ground) {
            if (y_vel < 0) {
                y_vel = 0;
            }
        }

        std::pair<std::vector<EllipsoidTriangleCollision>, glm::vec3> p =
            m_gameobject->getComponent<EllipsoidComponent>()->checkCollisionAndTranslate(old_pos, t->getPos(), true);
        //std::cout << p.first.size() << std::endl;

        // ************************************************************************************
        // if we collided with any triangles with upward-facing normals, then we are on the ground
        on_ground = false;
        for (int i = 0; i < p.first.size(); i++) {
            if (glm::dot(glm::vec3(0,1,0), p.first[i].normal) > 0) {
                on_ground = true;
                falling = false;
            }
        }

        // if we don't move laterally, then if we are on ground, we don't need to move at all
        if (on_ground) {
            t->setPos(old_pos);
        }
        return;
    }

    if (invincible) {
        saved_invincible_time += seconds;
        invincible_flicker_time += seconds;
        if (invincible_flicker_time > 2*FLICKER_TIME) {
            invincible_flicker_time = 0;
        } else if (invincible_flicker_time > FLICKER_TIME) {
            anim_comp->setDraw(false);
        } else {
            anim_comp->setDraw(true);
        }
        if (saved_invincible_time > TOTAL_INVINCIBLE_TIME) {
            anim_comp->setDraw(true);
            invincible = false;
            saved_invincible_time = 0;
            invincible_flicker_time = 0;
        }
    }

    bool moving_laterally = false;
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

    if (Input::getPressed("W") && Input::getPressed("D")) {
        if (on_ground && shooting) {
            anim_comp->setAnimation("run_diagonal_right_shoot");
        } else if (on_ground) {
            anim_comp->setAnimation("run_diagonal_right");
        }
    } else if (Input::getPressed("W") && Input::getPressed("A")) {
        if (on_ground && shooting) {
            anim_comp->setAnimation("run_diagonal_left_shoot");
        } else if (on_ground) {
            anim_comp->setAnimation("run_diagonal_left");
        }
    } else if (Input::getPressed("S") && Input::getPressed("A")) {
        if (on_ground && shooting) {
            anim_comp->setAnimation("run_diagonal_left_shoot");
        } else if (on_ground) {
            anim_comp->setAnimation("run_diagonal_left");
        }
    } else if (Input::getPressed("S") && Input::getPressed("D")) {
        if (on_ground && shooting) {
            anim_comp->setAnimation("run_diagonal_right_shoot");
        } else if (on_ground) {
            anim_comp->setAnimation("run_diagonal_right");
        }
    } else if (Input::getPressed("D")) {
        if (on_ground && shooting) {
            anim_comp->setAnimation("strafe_right_shoot");
        } else if (on_ground) {
            anim_comp->setAnimation("strafe_right");
        }
    } else if (Input::getPressed("S")) {
        if (on_ground && shooting) {
            anim_comp->setAnimation("back_shoot");
        } else if (on_ground) {
            anim_comp->setAnimation("back");
        }
    } else if (Input::getPressed("A")) {
        if (on_ground && shooting) {
            anim_comp->setAnimation("strafe_left_shoot");
        } else if (on_ground) {
            anim_comp->setAnimation("strafe_left");
        }
    } else if (Input::getPressed("W")) {
        if (on_ground && shooting) {
            anim_comp->setAnimation("run_and_shoot");
        } else if (on_ground) {
            anim_comp->setAnimation("run");
        }
    }

    // calculate and the set the new position we would have assuming we did not have collisions in this tick
    y_vel += GRAVITY * seconds;
    t->setPos(glm::vec3(t->getPos().x, t->getPos().y + y_vel * seconds, t->getPos().z));

    // ********************************************************************
    // if we are on the ground, set y_vel to 0
    if (on_ground) {
        if (y_vel < 0) {
            y_vel = 0;
        }
    }

    // jumping
    if (Input::getPressed("SPACE") && on_ground) {
        jump_queued = true;
        on_ground = false;
        jump_anim_time = 0;
        y_vel = JUMP_SPEED;
        anim_comp->setAnimation("jump");
    }

    if (y_vel < -10) {
        if (shooting) {
            anim_comp->setAnimation("falling_and_shoot");
        } else {
            anim_comp->setAnimation("falling");
        }
        falling = true;
        jump_anim_time = 0;
    } else if (!on_ground && std::abs(y_vel) > 15) {
        if (shooting) {
            anim_comp->setAnimation("jump_and_shoot");
        } else {
            anim_comp->setAnimation("jump");
        }
    }

    std::pair<std::vector<EllipsoidTriangleCollision>, glm::vec3> p =
            m_gameobject->getComponent<EllipsoidComponent>()->checkCollisionAndTranslate(old_pos, t->getPos(), true);
    //std::cout << p.first.size() << std::endl;

    // ************************************************************************************
    // if we collided with any triangles with upward-facing normals, then we are on the ground
    on_ground = false;
    for (int i = 0; i < p.first.size(); i++) {
        if (glm::dot(glm::vec3(0,1,0), p.first[i].normal) > 0) {
            on_ground = true;
            falling = false;
        }
    }

    // if we don't move laterally, then if we are on ground, we don't need to move at all
    if (!moving_laterally && on_ground) {
        t->setPos(old_pos);
        if (shooting) {
            anim_comp->setAnimation("shoot_rest");
        } else {
            anim_comp->setAnimation("rest");
        }
    }

    // TODO: stop jump early if hit head on ceiling
}

void PlatformerPlayerControlComponent::shoot(float seconds) {
    if (Input::getPressed("MOUSELEFT") && !recovering) {
        shooting = true;
        glm::vec3 look = glm::normalize(m_gameobject->getComponent<CameraComponent>()->getCamera()->getLook() + glm::vec3(0,.3,0));
        glm::vec3 horizontal_look = glm::normalize(glm::vec3(look.x, 0, look.z));
        glm::vec3 right = glm::normalize(glm::cross(look, glm::vec3(0,1,0)));
        glm::vec3 pos = m_gameobject->getComponent<TransformComponent>()->getPos() + glm::vec3(0,1.3,0) + horizontal_look * 1.6f;
        int random = std::rand() % 2;
        std::shared_ptr<PlayerBullet> bullet;
        if (random == 1) {
            bullet = std::make_shared<PlayerBullet>(pos + .2f*right, look);
        } else {
            bullet = std::make_shared<PlayerBullet>(pos - .2f*right, look);
        }
        m_gameobject->getGameWorld()->addGameObject(bullet);

        if (saved_laser_time > LASER_TIME) {
            saved_laser_time = 0;
            //m_gameobject->getComponent<SoundComponent>()->playSound(":/sounds/laser.wav");
        }
    } else {
        shooting = false;
    }
    saved_laser_time += seconds;
}

void PlatformerPlayerControlComponent::setPositionOfCamera() {
    glm::vec3 saved_player_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    glm::vec3 look = camera->getLook();
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    glm::vec3 camera_pos = t->getPos() + glm::vec3(0,CAMERA_HEIGHT,0) - third_person_cam_pos*look;
    std::pair<std::vector<EllipsoidTriangleCollision>, glm::vec3> p =
        m_gameobject->getComponent<EllipsoidComponent>()->checkCollisionAndTranslate(saved_player_pos + glm::vec3(0,CAMERA_HEIGHT,0), camera_pos, true);
    if (p.first.size() > 0) {
        camera->setEye(p.first[0].center);
    } else {
        camera->setEye(camera_pos);
    }
    t->setPos(saved_player_pos);
}

void PlatformerPlayerControlComponent::onMouseDragged(int deltaX, int deltaY) {
    m_deltaX = deltaX;
    m_deltaY = deltaY;
    std::shared_ptr<Camera> camera = m_gameobject->getComponent<CameraComponent>()->getCamera();
    camera->rotate(-m_deltaX / 100.0f * MOUSE_SENSITIVITY, -m_deltaY / 100.0f * MOUSE_SENSITIVITY);
    std::shared_ptr<TransformComponent> t = m_gameobject->getComponent<TransformComponent>();
    if (!game_over) {
        t->changeYaw(-m_deltaX / 100.0f * MOUSE_SENSITIVITY);
    }
}

void PlatformerPlayerControlComponent::onKeyPressed(QKeyEvent *event) {
    if (event->key() == Qt::Key_Minus) m_gameobject->getGameWorld()->getScreen()->setAppReadyToRestart();
    if (event->key() == Qt::Key_T) {
        //use_third_person = !use_third_person;
        //m_gameobject->getComponent<PrimitiveDrawableComponent>()->setDraw(use_third_person);
    }
    if (event->key() == Qt::Key_P) m_gameobject->getGameWorld()->getScreen()->getApp()->changeScreen("pause");
}

void PlatformerPlayerControlComponent::onKeyReleased(QKeyEvent *event) {
}

void PlatformerPlayerControlComponent::onKeyRepeated(QKeyEvent *event) {
}

void PlatformerPlayerControlComponent::onMousePressed(QMouseEvent *event) {
    if (event->button() == Qt::MouseButton::RightButton && saved_dodge_recharge_time > TOTAL_DODGE_RECHARGE_TIME && !dodging) {
        saved_dodge_recharge_time = 0;
        dodging = true;
    }
}

void PlatformerPlayerControlComponent::onMouseReleased(QMouseEvent *event) {
}

void PlatformerPlayerControlComponent::onWheelEvent(QWheelEvent *event) {
    if (use_third_person) {
        third_person_cam_pos = glm::clamp(third_person_cam_pos - .002f*event->angleDelta().y(),
                                          MIN_CAM_TRANSLATION, MAX_CAM_TRANSLATION);
    }
}
