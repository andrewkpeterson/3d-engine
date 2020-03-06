#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class GameWorld;

class TransformComponent : public Component
{
public:
    TransformComponent(glm::vec3 pos, float scale);
    ~TransformComponent() override;
    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;

    void setObjectToWorldTransform();
    void setObjectSpaceOrientation();
    void translate(glm::vec3 translation);
    void setPos(glm::vec3 position);
    glm::vec3 getPos();
    void setHeading(glm::vec2 h);
    void changeYaw(float theta);
    void changePitch(float theta);
    void changeRoll(float theta);
    void setYaw(float theta);
    void setPitch(float theta);
    void setRoll(float theta);
    void setScale(float size);
    float getPitch();
    float getRoll();
    float getYaw();

    void setObjectPos(glm::vec3 pos);
    void changeObjectYaw(float theta);
    void changeObjectPitch(float theta);
    void changeObjectRoll(float theta);
    void setObjectYaw(float theta);
    void setObjectPitch(float theta);
    void setObjectRoll(float theta);
    float getObjectPitch();
    float getObjectRoll();
    float getObjectYaw();

private:
    glm::vec3 m_pos;
    glm::vec2 m_heading;
    float roll;
    float pitch;
    float yaw;
    float m_scale;
    Graphics *g;
    glm::vec3 object_pos;
    float object_roll;
    float object_pitch;
    float object_yaw;
};

#endif // TRANSFORMCOMPONENT_H
