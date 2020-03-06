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

    void setObjectTransform();
    void translate(glm::vec3 translation);
    void setPos(glm::vec3 position);
    void setHeading(glm::vec2 h);
    void changeYaw(float theta);
    void changePitch(float theta);
    void changeRoll(float theta);
    void setYaw(float theta);
    void setPitch(float theta);
    void setRoll(float theta);
    void setScale(float size);
    glm::vec3 getPos();
private:
    glm::vec3 m_pos;
    glm::vec2 m_heading;
    float roll;
    float pitch;
    float yaw;
    float m_scale;
    Graphics *g;
};

#endif // TRANSFORMCOMPONENT_H
