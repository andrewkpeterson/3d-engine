#ifndef ENVIRONMENTCOMPONENT_H
#define ENVIRONMENTCOMPONENT_H

#include "Component.h"
#include "src/engine/util/obj.h"

class EnvironmentComponent : public Component
{
public:
    EnvironmentComponent(std::string mesh_file, std::string matname, std::string tex_file, std::string navmesh_file);
    ~EnvironmentComponent();

    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;
    const QList<OBJ::Triangle*> getTriangles();
    void draw();

private:
    std::shared_ptr<OBJ> navmesh;
    std::string m_matname;
    std::string shapename;
    Graphics *g;
};

#endif // ENVIRONMENTCOMPONENT_H
