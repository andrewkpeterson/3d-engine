#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class GameWorld;

class TransformComponent : public Component
{
public:
    TransformComponent(std::shared_ptr<GameObject> gameobject, glm::vec3 pos, float scale);
    ~TransformComponent() override;
    void addGameObjectToSystems() override;
    void removeGameObjectFromSystems() override;

    void setObjectTransform();
private:
    glm::vec3 m_pos;
    float m_scale;
    Graphics *g;
};

#endif // TRANSFORMCOMPONENT_H
