#ifndef CHUNKCONTAINERCOMPONENT_H
#define CHUNKCONTAINERCOMPONENT_H

#include <unordered_set>
#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/graphics/Chunk.h"

class ChunkDrawableComponent : public DrawableComponent
{
public:
    ChunkDrawableComponent(std::shared_ptr<Chunk> chunk, std::string texture_atlas_name);
    ~ChunkDrawableComponent();
    void drawSelf();


protected:
    std::shared_ptr<Chunk> m_chunk;
    std::string m_atlas_name;
    Material m_atlas;
    const int NUM_R_VECTORS = 6;
    const int NUM_BOUNDING_CORNERS = 8;
};

#endif // CHUNKCONTAINERCOMPONENT_H
