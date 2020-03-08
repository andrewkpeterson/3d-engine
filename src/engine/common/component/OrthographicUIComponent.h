#ifndef ORTHOGRAPHICUICOMPONENT_H
#define ORTHOGRAPHICUICOMPONENT_H

#include "DrawableComponent.h"
#include "src/engine/graphics/Graphics.h"

class OrthographicUIComponent : public DrawableComponent
{
public:
    OrthographicUIComponent(std::string matname, Material material, glm::vec3 offset);
    OrthographicUIComponent(std::string matname, glm::vec3 offset);
    ~OrthographicUIComponent();
    void addComponentToSystemsAndConnectComponents();
    void removeComponentFromSystems();

protected:
    glm::vec3 convertToScreenSpace(glm::vec3 pos, std::shared_ptr<Camera> camera);
    glm::vec3 m_offset;
    std::string m_matname;
};

#endif // ORTHOGRAPHICUICOMPONENT_H
