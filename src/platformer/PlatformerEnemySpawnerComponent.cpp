#include "PlatformerEnemySpawnerComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/platformer/prefabs/Enemy.h"

PlatformerEnemySpawnerComponent::PlatformerEnemySpawnerComponent() :
      spawn_time(2), enemies_spawned(0)
{

}

PlatformerEnemySpawnerComponent::~PlatformerEnemySpawnerComponent()
{

}

void PlatformerEnemySpawnerComponent::tick(float seconds) {
    saved_time += seconds;

    for (auto it = active_enemies.begin(); it != active_enemies.end(); it++) {
        if (!m_gameobject->getGameWorld()->checkIfGameObjectExists((*it).second)) {
            active_enemies.erase(it);
            break; //break out so that the iterator does not cause problems
        }
    }

    if (saved_time > spawn_time && active_enemies.size() < MAX_ENEMIES) {
        enemies_spawned++;
        saved_time = 0;
        bool found = false;
        int spawn_point;
        while (!found) {
            int idx = std::rand() % spawn_points.size();
            if (active_enemies.find(idx) == active_enemies.end()) {
                spawn_point = idx;
                found = true;
            }
        }

        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(spawn_points[spawn_point]);
        m_gameobject->getGameWorld()->addGameObject(enemy);
        active_enemies[spawn_point] = "enemy";
        if (enemies_spawned < 10) {
            spawn_time = EASY_TIME;
        } else if (enemies_spawned < 20) {
            spawn_time = MEDIUM_TIME;
        } else {
            spawn_time = HARD_TIME;
        }
    }

}
