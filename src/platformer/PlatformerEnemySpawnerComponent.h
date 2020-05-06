#ifndef PLATFORMERENEMYSPAWNERCOMPONENT_H
#define PLATFORMERENEMYSPAWNERCOMPONENT_H

#include "src/engine/common/component/TickComponent.h"
#include <set>

class PlatformerEnemySpawnerComponent : public TickComponent
{
public:
    PlatformerEnemySpawnerComponent();
    ~PlatformerEnemySpawnerComponent();

    void tick(float seconds);

private:
    const std::vector<glm::vec3> spawn_points = {glm::vec3(-20,10,-20), glm::vec3(0,10,-20), glm::vec3(20,10,20),
                                                 glm::vec3(-20,10,0), glm::vec3(20,10,-20), glm::vec3(-20,10,20)};
    std::map<int, std::string> active_enemies;

    float spawn_time;
    float saved_time;
    int enemies_spawned;
    int MAX_ENEMIES = 3;

    int EASY_TIME = 15;
    int MEDIUM_TIME = 10;
    int HARD_TIME = 7;
};

#endif // PLATFORMERENEMYSPAWNERCOMPONENT_H
