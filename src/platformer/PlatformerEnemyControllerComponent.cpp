#include "PlatformerEnemyControllerComponent.h"
#include "src/platformer/PlatformerEnemyBulletControllerComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/SphereCollisionComponent.h"


PlatformerEnemyControllerComponent::PlatformerEnemyControllerComponent() :
      saved_time(0), sphere_offset(0), spread_offset(0), radial_offset(0), shoot_time(0)
{

}

PlatformerEnemyControllerComponent::~PlatformerEnemyControllerComponent()
{

}

void PlatformerEnemyControllerComponent::tick(float seconds) {

    currentPattern = BP_SPHERE;

    if (saved_time > shoot_time) {
        saved_time = 0;
        if (currentPattern == BP_STRAIGHT) {
            shoot_time = STRAIGHT_SHOOT_TIME;
            Material mat;
            mat.color = glm::vec3(1.0,0,0);
            float offset = M_PI / 5.0f * std::sin(spread_offset);
            spread_offset += seconds * 20;
            glm::vec3 enemy_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
            glm::vec3 player_pos = m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
            glm::vec3 bullet_dir = glm::normalize(player_pos - enemy_pos);
            std::shared_ptr<GameObject> bullet = std::make_shared<GameObject>();
            bullet->addComponent<PlatformerEnemyBulletControllerComponent>(
                std::make_shared<PlatformerEnemyBulletControllerComponent>(bullet_dir, 20, glm::vec3(0,0,0), false, glm::vec3(0,0,0)));
            bullet->addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(false, true, .75));
            bullet->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "bulletmat", mat));
            bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
            bullet->getComponent<TransformComponent>()->setScale(1.5f);
            bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
            m_gameobject->getGameWorld()->addGameObject(bullet);
        } else if (currentPattern == BP_RADIAL_1) {
            shoot_time = RADIAL_SHOOT_TIME;
            radial_offset += seconds * 20;
            Material mat;
            mat.color = glm::vec3(1.0,0,0);
            glm::vec3 enemy_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
            glm::vec3 player_pos = m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
            glm::vec3 bullet_dir = glm::normalize(player_pos - enemy_pos);
            float theta = std::acos(bullet_dir.z) + radial_offset;
            float phi = std::atan2(bullet_dir.y, bullet_dir.x);
            float x = std::sin(theta) * std::cos(phi);
            float y = std::sin(theta) * std::sin(phi);
            float z = std::cos(theta);
            std::shared_ptr<GameObject> bullet = std::make_shared<GameObject>();
            bullet->addComponent<PlatformerEnemyBulletControllerComponent>(
                std::make_shared<PlatformerEnemyBulletControllerComponent>(glm::vec3(x,y,z), 20, glm::vec3(0,0,0), false, glm::vec3(0,0,0)));
            bullet->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "bulletmat", mat));
            bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
            bullet->getComponent<TransformComponent>()->setScale(1.5f);
            bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
            m_gameobject->getGameWorld()->addGameObject(bullet);
        } else if (currentPattern == BP_RADIAL_2) {
            shoot_time = RADIAL_SHOOT_TIME;
            radial_offset += seconds * 20;
            Material mat;
            mat.color = glm::vec3(1.0,0,0);
            glm::vec3 enemy_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
            glm::vec3 player_pos = m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
            glm::vec3 bullet_dir = glm::normalize(player_pos - enemy_pos);
            float theta = std::acos(bullet_dir.z);
            float phi = std::atan2(bullet_dir.y, bullet_dir.x) + radial_offset;
            float x = std::sin(theta) * std::cos(phi);
            float y = std::sin(theta) * std::sin(phi);
            float z = std::cos(theta);
            std::shared_ptr<GameObject> bullet = std::make_shared<GameObject>();
            bullet->addComponent<PlatformerEnemyBulletControllerComponent>(
                std::make_shared<PlatformerEnemyBulletControllerComponent>(glm::vec3(x,y,z), 20, glm::vec3(0,0,0), false, glm::vec3(0,0,0)));
            bullet->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "bulletmat", mat));
            bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
            bullet->getComponent<TransformComponent>()->setScale(1.5f);
            bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
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
                        std::shared_ptr<GameObject> bullet = std::make_shared<GameObject>();
                        Material mat;
                        mat.color = glm::vec3(1.0,0,0);
                        bullet->addComponent<PlatformerEnemyBulletControllerComponent>(
                            std::make_shared<PlatformerEnemyBulletControllerComponent>(glm::vec3(x,y,z), 20, glm::vec3(0,0,0), false, glm::vec3(0,0,0)));
                        bullet->addComponent<SphereCollisionComponent>(std::make_shared<SphereCollisionComponent>(false, true, 1.5));
                        bullet->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "bulletmat", mat));
                        bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
                        bullet->getComponent<TransformComponent>()->setScale(1.5f);
                        bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
                        m_gameobject->getGameWorld()->addGameObject(bullet);
                    }
                }
            }
        } else if (currentPattern == BP_SPREAD_1) {
            shoot_time = SPREAD_SHOOT_TIME;
            Material mat;
            mat.color = glm::vec3(1.0,0,0);
            float offset = M_PI / 5.0f * std::sin(spread_offset);
            spread_offset += seconds * 20;
            glm::vec3 enemy_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
            glm::vec3 player_pos = m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
            glm::vec3 bullet_dir = glm::normalize(player_pos - enemy_pos);
            float theta = std::acos(bullet_dir.z) + offset;
            float phi = std::atan2(bullet_dir.y, bullet_dir.x);
            float x = std::sin(theta) * std::cos(phi);
            float y = std::sin(theta) * std::sin(phi);
            float z = std::cos(theta);
            std::shared_ptr<GameObject> bullet = std::make_shared<GameObject>();
            bullet->addComponent<PlatformerEnemyBulletControllerComponent>(
                std::make_shared<PlatformerEnemyBulletControllerComponent>(glm::vec3(x,y,z), 20, glm::vec3(0,0,0), false, glm::vec3(0,0,0)));
            bullet->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "bulletmat", mat));
            bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
            bullet->getComponent<TransformComponent>()->setScale(1.5f);
            bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
            m_gameobject->getGameWorld()->addGameObject(bullet);
        } else if (currentPattern == BP_SPREAD_2) {
            shoot_time = SPREAD_SHOOT_TIME;
            Material mat;
            mat.color = glm::vec3(1.0,0,0);
            float offset = M_PI / 5.0f * std::sin(spread_offset);
            spread_offset += seconds * 20;
            glm::vec3 enemy_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
            glm::vec3 player_pos = m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
            glm::vec3 bullet_dir = glm::normalize(player_pos - enemy_pos);
            float theta = std::acos(bullet_dir.z);
            float phi = std::atan2(bullet_dir.y, bullet_dir.x) + offset;
            float x = std::sin(theta) * std::cos(phi);
            float y = std::sin(theta) * std::sin(phi);
            float z = std::cos(theta);
            std::shared_ptr<GameObject> bullet = std::make_shared<GameObject>();
            bullet->addComponent<PlatformerEnemyBulletControllerComponent>(
                std::make_shared<PlatformerEnemyBulletControllerComponent>(glm::vec3(x,y,z), 20, glm::vec3(0,0,0), false, glm::vec3(0,0,0)));
            bullet->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "bulletmat", mat));
            bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
            bullet->getComponent<TransformComponent>()->setScale(1.5f);
            bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
            m_gameobject->getGameWorld()->addGameObject(bullet);
        } else if (currentPattern == BP_WALL) {
            shoot_time = WALL_SHOOT_TIME;
            Material mat;
            mat.color = glm::vec3(1.0,0,0);
            glm::vec3 enemy_pos = m_gameobject->getComponent<TransformComponent>()->getPos();
            glm::vec3 player_pos = m_gameobject->getGameWorld()->getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
            glm::vec3 bullet_dir = glm::normalize(player_pos - enemy_pos);
            float center_theta = std::acos(bullet_dir.z);
            float center_phi = std::atan2(bullet_dir.y, bullet_dir.x);

            for (int row = -NUM_WALL_BULLETS_PARAM / 2; row < NUM_WALL_BULLETS_PARAM / 2; row++) {
                for (int col = -NUM_WALL_BULLETS_PARAM / 2; col < NUM_WALL_BULLETS_PARAM / 2; col++) {
                    float phi = center_phi + .1* M_PI * float(row) / float(NUM_SPHERE_BULLETS_PARAM / 2);
                    float theta = center_theta + .1 * M_PI * float(col) / float(NUM_SPHERE_BULLETS_PARAM / 2);
                    float x = std::sin(theta) * std::cos(phi);
                    float y = std::sin(theta) * std::sin(phi);
                    float z = std::cos(theta);
                    std::shared_ptr<GameObject> bullet = std::make_shared<GameObject>();
                    bullet->addComponent<PlatformerEnemyBulletControllerComponent>(
                        std::make_shared<PlatformerEnemyBulletControllerComponent>(glm::vec3(x,y,z), 20, glm::vec3(0,0,0), false, glm::vec3(0,0,0)));
                    bullet->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("sphere", "bulletmat", mat));
                    bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
                    bullet->getComponent<TransformComponent>()->setScale(1.5f);
                    bullet->getComponent<TransformComponent>()->setPos(m_gameobject->getComponent<TransformComponent>()->getPos());
                    m_gameobject->getGameWorld()->addGameObject(bullet);
                }
            }
        }
    } else {
        saved_time = saved_time + seconds;
    }
}
