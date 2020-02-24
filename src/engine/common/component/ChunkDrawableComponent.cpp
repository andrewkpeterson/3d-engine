#include "ChunkDrawableComponent.h"
#include "ChunkComponent.h"
#include "TransformComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "engine/graphics/Texture.h"

ChunkDrawableComponent::ChunkDrawableComponent(std::string texture_atlas_name) :
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
    if (shouldDraw && m_gameobject->getComponent<ChunkComponent>()->isBuilt()) {
        const std::vector<glm::vec4> vectors = m_gameobject->getGameWorld()->getSystem<CameraSystem>()->
                                           getCurrentMainCameraComponent()->getCamera()->getRVectors();
        std::shared_ptr<Chunk> chunk = m_gameobject->getComponent<ChunkComponent>()->getChunk();
        const std::vector<glm::vec4> bounds = chunk->getBounds();
        for (int i = 0; i < NUM_R_VECTORS; i++) {
            bool corner_behind = true;
            for (int corner_idx = 0; corner_idx < NUM_BOUNDING_CORNERS; corner_idx++) {
                if (glm::dot(bounds[corner_idx], vectors[i]) >= 0) {
                    corner_behind = false;
                }
            }
            if (corner_behind) {
                return;
            }
        }
        g->setMaterial(m_atlas_name);
        g->clearTransform();
        // for the purposes of frustum culling, chunks should not have a model matrix. So, we don't need to set a transform.
        chunk->draw(g);
    }
}
