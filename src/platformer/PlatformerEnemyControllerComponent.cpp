#include "PlatformerEnemyControllerComponent.h"
#include "src/platformer/PlatformerEnemyBulletControllerComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/SphereCollisionComponent.h"
#include "src/platformer/prefabs/EnemyBullet.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/platformer/prefabs/Explosion.h"
#include "src/engine/common/component/UIComponent.h"



PlatformerEnemyControllerComponent::PlatformerEnemyControllerComponent() :
      saved_time(0), sphere_offset(0), spread_offset(0), radial_offset(0), shoot_time(0),
      health_bar(6000), saved_pattern_time(0), saved_spawn_time(0), spawning_in(true),
      flicker_time(0)
{
    currentPattern = EnemyBulletPattern(std::rand() % EnemyBulletPattern::BP_WALL + 1);
}

PlatformerEnemyControllerComponent::~PlatformerEnemyControllerComponent()
{

}

void PlatformerEnemyControllerComponent::addComponentToSystemsAndConnectComponents() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
    m_gameobject->getComponent<SphereCollisionComponent>()->
        setCollisionCallback(std::bind(&PlatformerEnemyControllerComponent::handleCollisionResolutionAndResponse,
                                       this, std::placeholders::_1));
}

void PlatformerEnemyControllerComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
}

void PlatformerEnemyControllerComponent::handleCollisionResolutionAndResponse(Collision collision) {
    int score = std::stoi(m_gameobject->getGameWorld()->getGameObjectByID("HUD")->getComponent<UIComponent>()->getElement("score")->getText()) + 10;
    m_gameobject->getGameWorld()->getGameObjectByID("HUD")->getComponent<UIComponent>()->getElement("score")->setText(std::to_string(score));
    int random = std::rand() % 10;
    if (random == 1) {
        glm::vec3 dir = glm::normalize(glm::vec3(2 * float(std::rand()) / INT_MAX - 1, 2* float(std::rand()) / INT_MAX - 1, 2*float(std::rand()) / INT_MAX - 1));
        glm::vec3 explosion_pos = m_gameobject->getComponent<TransformComponent>()->getPos() +
                                  .5f * m_gameobject->getComponent<TransformComponent>()->getScale() * dir;
        int random_size = (std::rand() % 100) * .03;
        int random_size_change = (std::rand() % 10) * .1;
        std::shared_ptr<Explosion> explosion = std::make_shared<Explosion>(explosion_pos, .1, random_size, .3);
        m_gameobject->getGameWorld()->addGameObject(explosion);
    }
    health_bar -= 1;
}

void PlatformerEnemyControllerComponent::tick(float seconds) {
    if (spawning_in) {
        saved_spawn_time += seconds;
        if (saved_spawn_time > SPAWN_IN_TIME) {
            spawning_in = false;
        }
        flicker_time += seconds;
        if (flicker_time > 2*FLICKER_TIME) {
            flicker_time = 0;
        } else if (flicker_time > FLICKER_TIME) {
            m_gameobject->getComponent<PrimitiveDrawableComponent>()->setDraw(false);
        } else {
            m_gameobject->getComponent<PrimitiveDrawableComponent>()->setDraw(true);
        }
        return;
    } else {
        m_gameobject->getComponent<PrimitiveDrawableComponent>()->setDraw(true);
    }

    saved_pattern_time += seconds;

    if (health_bar < 0) {
        glm::vec3 explosion_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
        std::shared_ptr<Explosion> explosion = std::make_shared<Explosion>(explosion_pos, .2, 5, .5);
        m_gameobject->getGameWorld()->addGameObject(explosion);
        m_gameobject->getGameWorld()->markGameObjectForDeletion(m_gameobject->getID());
    }

    if (saved_pattern_time > PATTERN_SWITCH_TIME) {
        saved_pattern_time = 0;
        currentPattern = EnemyBulletPattern(std::rand() % EnemyBulletPattern::BP_WALL + 1);
    }

    if (saved_time > shoot_time) {
        saved_time = 0;
        glm::vec3 start_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
        shoot_time = WALL_SHOOT_TIME;
        glm::vec3 enemy_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
        glm::vec3 player_pos = m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
        glm::vec3 bullet_dir = glm::normalize(player_pos - enemy_pos);
        float center_theta = std::acos(bullet_dir.z);
        float center_phi = std::atan2(bullet_dir.y, bullet_dir.x);

        if (currentPattern == BP_STRAIGHT) {
            shoot_time = STRAIGHT_SHOOT_TIME;
            glm::vec3 enemy_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
            glm::vec3 player_pos = m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
            glm::vec3 bullet_dir = glm::normalize(player_pos - enemy_pos);
            std::shared_ptr<EnemyBullet> bullet = std::make_shared<EnemyBullet>(start_pos, bullet_dir, 7, 1.5);
            m_gameobject->getGameWorld()->addGameObject(bullet);
        } else if (currentPattern == BP_RADIAL_1) {
            shoot_time = RADIAL_SHOOT_TIME;
            radial_offset += seconds * 20;
            float theta = center_theta + radial_offset;
            float phi = center_phi;
            float x = std::sin(theta) * std::cos(phi);
            float y = std::sin(theta) * std::sin(phi);
            float z = std::cos(theta);
            std::shared_ptr<EnemyBullet> bullet = std::make_shared<EnemyBullet>(start_pos, glm::vec3(x,y,z), 7, 1.5);
            m_gameobject->getGameWorld()->addGameObject(bullet);
        } else if (currentPattern == BP_RADIAL_2) {
            shoot_time = RADIAL_SHOOT_TIME;
            radial_offset += seconds * 20;
            float theta = center_theta;
            float phi = center_phi + radial_offset;
            float x = std::sin(theta) * std::cos(phi);
            float y = std::sin(theta) * std::sin(phi);
            float z = std::cos(theta);
            std::shared_ptr<EnemyBullet> bullet = std::make_shared<EnemyBullet>(start_pos, glm::vec3(x,y,z), 7, 1.5);
            m_gameobject->getGameWorld()->addGameObject(bullet);
        } else if (currentPattern == BP_SPHERE) {
            shoot_time = SPHERE_SHOOT_TIME;
            sphere_offset += seconds * 5.0;
            for (int theta_i = 0; theta_i <= NUM_SPHERE_BULLETS_PARAM; theta_i++) {
                for (int phi_i = 0; phi_i <= NUM_SPHERE_BULLETS_PARAM; phi_i++) {
                    if (theta_i != 0 && theta_i != NUM_SPHERE_BULLETS_PARAM) {
                        float phi = 2*M_PI * float(phi_i) / float(NUM_SPHERE_BULLETS_PARAM) + sphere_offset;
                        float theta = M_PI * float(theta_i) / float(NUM_SPHERE_BULLETS_PARAM);
                        float x = std::sin(theta) * std::cos(phi);
                        float y = std::sin(theta) * std::sin(phi);
                        float z = std::cos(theta);
                        std::shared_ptr<EnemyBullet> bullet = std::make_shared<EnemyBullet>(start_pos, glm::vec3(x,y,z), 7, 1.5);
                        m_gameobject->getGameWorld()->addGameObject(bullet);
                    }
                }
            }
        } else if (currentPattern == BP_SPREAD_1) {
            shoot_time = SPREAD_SHOOT_TIME;
            float offset = M_PI / 5.0f * std::sin(spread_offset);
            spread_offset += seconds * 20;
            float theta = center_theta + offset;
            float phi = center_phi;
            float x = std::sin(theta) * std::cos(phi);
            float y = std::sin(theta) * std::sin(phi);
            float z = std::cos(theta);
            std::shared_ptr<EnemyBullet> bullet = std::make_shared<EnemyBullet>(start_pos, glm::vec3(x,y,z), 7, 1.5);
            m_gameobject->getGameWorld()->addGameObject(bullet);
        } else if (currentPattern == BP_SPREAD_2) {
            shoot_time = SPREAD_SHOOT_TIME;
            float offset = M_PI / 5.0f * std::sin(spread_offset);
            spread_offset += seconds * 20;
            float theta = center_theta;
            float phi = center_phi + offset;
            float x = std::sin(theta) * std::cos(phi);
            float y = std::sin(theta) * std::sin(phi);
            float z = std::cos(theta);
            std::shared_ptr<EnemyBullet> bullet = std::make_shared<EnemyBullet>(start_pos, glm::vec3(x,y,z), 7, 1.5);
            m_gameobject->getGameWorld()->addGameObject(bullet);
        } else if (currentPattern == BP_WALL) {
            for (int row = -NUM_WALL_BULLETS_PARAM / 2; row < NUM_WALL_BULLETS_PARAM / 2; row++) {
                for (int col = -NUM_WALL_BULLETS_PARAM / 2; col < NUM_WALL_BULLETS_PARAM / 2; col++) {
                    float phi = center_phi + .1* M_PI * float(row) / float(NUM_SPHERE_BULLETS_PARAM / 2);
                    float theta = center_theta + .1 * M_PI * float(col) / float(NUM_SPHERE_BULLETS_PARAM / 2);
                    float x = std::sin(theta) * std::cos(phi);
                    float y = std::sin(theta) * std::sin(phi);
                    float z = std::cos(theta);
                    std::shared_ptr<EnemyBullet> bullet = std::make_shared<EnemyBullet>(start_pos, glm::vec3(x,y,z), 7, 1.5);
                    m_gameobject->getGameWorld()->addGameObject(bullet);
                }
            }
        }
    } else {
        saved_time = saved_time + seconds;
        //std::cout << "tried" << std::endl;
    }
}
