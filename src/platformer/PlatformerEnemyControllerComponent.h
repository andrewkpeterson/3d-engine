#ifndef PLATFORMERENEMYCONTROLLERCOMPONENT_H
#define PLATFORMERENEMYCONTROLLERCOMPONENT_H

#include "src/engine/common/component/TickComponent.h"

enum EnemyBulletPattern {
    BP_STRAIGHT, BP_RADIAL_1, BP_RADIAL_2, BP_SPHERE, BP_SPREAD_1, BP_SPREAD_2, BP_WALL
};

class PlatformerEnemyControllerComponent : public TickComponent
{
public:
    PlatformerEnemyControllerComponent();
    ~PlatformerEnemyControllerComponent();
    void tick(float seconds) override;

private:
    float shoot_time;
    const float STRAIGHT_SHOOT_TIME = .2;
    const float RADIAL_SHOOT_TIME = .03;
    const float ACCELERATE_SHOOT_TIME = .2;
    const float SPHERE_SHOOT_TIME = .2;
    const float SPREAD_SHOOT_TIME = .05;
    const float WALL_SHOOT_TIME = .6;

    const int NUM_SPHERE_BULLETS_PARAM = 10;
    float sphere_offset;

    const int NUM_WALL_BULLETS_PARAM = 6;

    float spread_offset;

    float radial_offset;

    EnemyBulletPattern currentPattern;
    float saved_time;

};

#endif // PLATFORMERENEMYCONTROLLERCOMPONENT_H
