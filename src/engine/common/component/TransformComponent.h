#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class GameWorld;

class TransformComponent : public Component
{
public:
    TransformComponent(GameObject *gameobject, glm::vec3 pos, float scale);
    ~TransformComponent() override;
    void addComponentToSystems() override;
    void removeComponentFromSystems() override;

    void setObjectTransform();
    void translate(glm::vec3 translation);
    void setPos(glm::vec3 position);
    glm::vec3 getPos();
private:
    glm::vec3 m_pos;
    float m_scale;
    Graphics *g;
};

#endif // TRANSFORMCOMPONENT_H
