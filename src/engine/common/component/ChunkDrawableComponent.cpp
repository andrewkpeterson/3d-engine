#include "ChunkDrawableComponent.h"
#include "TransformComponent.h"
#include "engine/graphics/Texture.h"

ChunkDrawableComponent::ChunkDrawableComponent(std::shared_ptr<Chunk> chunk, std::string texture_atlas_name) :
    m_chunk(chunk),
    m_atlas_name(texture_atlas_name)
{
    m_atlas.textureName = texture_atlas_name;
    m_atlas.materialName = texture_atlas_name;
    g->addTexture(texture_atlas_name, texture_atlas_name, Texture::FILTER_METHOD::NEAREST);
    //m_atlas.textureRepeat = glm::vec2(10,10);
    g->addMaterial(m_atlas_name, m_atlas);
}

ChunkDrawableComponent::~ChunkDrawableComponent()
{

}

void ChunkDrawableComponent::drawSelf() {
    // a chunk should get the current camera from the gameworld and check itself against the view planes
    g->setMaterial(m_atlas_name);
    g->clearTransform();
    // for the purposes of frustum culling, chunks should not have a model matrix
    m_chunk->draw(g);
}
