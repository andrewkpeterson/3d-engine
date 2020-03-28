#include "EnvironmentComponent.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/graphics/ResourceLoader.h"
#include "src/engine/graphics/Shape.h"
#include "src/engine/common/system/EnvironmentSystem.h"

EnvironmentComponent::EnvironmentComponent(std::string mesh_file, std::string matname,
                                           std::string tex_file, std::string navmesh_file) :
    Component(),
    navmesh(std::make_unique<OBJ>(QString(navmesh_file.c_str()))),
    m_matname(matname),
    shapename(mesh_file)
{
    std::shared_ptr<Shape> shape = std::make_shared<Shape>(mesh_file);
    ResourceLoader::readObj(mesh_file.c_str(), shape);
    Material mat;
    mat.textureName = tex_file;
    g = Graphics::getGlobalInstance();
    g->addMaterial(matname, mat);
    g->addShape(mesh_file, shape);
    g->addTexture(tex_file, tex_file, Texture::FILTER_METHOD::LINEAR);

}

EnvironmentComponent::~EnvironmentComponent()
{

}

void EnvironmentComponent::addComponentToSystemsAndConnectComponents()
{

}

void EnvironmentComponent::removeComponentFromSystems()
{

}

const QList<OBJ::Triangle*> EnvironmentComponent::getTriangles() {
    return navmesh->triangles;
}

void EnvironmentComponent::draw() {
    g->clearTransform();
    g->setMaterial(m_matname);
    g->drawShape(shapename);
}
