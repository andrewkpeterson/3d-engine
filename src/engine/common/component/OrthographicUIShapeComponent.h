#ifndef ORTHOGRAPHICUISHAPECOMPONENT_H
#define ORTHOGRAPHICUISHAPECOMPONENT_H

#include "DrawableComponent.h"
#include "src/engine/graphics/Graphics.h"
#include "OrthographicUIComponent.h"

class OrthographicUIShapeComponent : public OrthographicUIComponent
{
public:
    OrthographicUIShapeComponent(std::string geometry, std::string matname, Material material, glm::vec3 offset, glm::vec3 m_size);
    OrthographicUIShapeComponent(std::string geometry, std::string matname, glm::vec3 offset, glm::vec3 m_size);
    ~OrthographicUIShapeComponent();
    void drawSelf(std::shared_ptr<Camera> camera) override;
    void setSize(glm::vec3 new_size);

private:
    std::string m_geometry;
    glm::vec3 m_size;
};

#endif // ORTHOGRAPHICUISHAPECOMPONENT_H
