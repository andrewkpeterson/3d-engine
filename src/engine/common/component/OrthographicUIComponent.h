#ifndef ORTHOGRAPHICUICOMPONENT_H
#define ORTHOGRAPHICUICOMPONENT_H

#include "DrawableComponent.h"
#include "src/engine/graphics/Graphics.h"

class OrthographicUIComponent : public DrawableComponent
{
public:
    OrthographicUIComponent(std::string geometry, std::string matname, Material material);
    OrthographicUIComponent(std::string geometry, std::string matname);
    ~OrthographicUIComponent();
    void addComponentToSystemsAndConnectComponents();
    void removeComponentFromSystems();
    void setDraw(bool draw);
    void drawSelf(std::shared_ptr<Camera> camera);
    glm::vec3 convertToScreenSpace(glm::vec3 pos, std::shared_ptr<Camera> camera);

private:
    std::string m_matname;
    std::string m_geometry;
    std::shared_ptr<Camera> m_camera;
};

#endif // ORTHOGRAPHICUICOMPONENT_H
