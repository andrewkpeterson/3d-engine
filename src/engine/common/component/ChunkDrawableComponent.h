#ifndef CHUNKCONTAINERCOMPONENT_H
#define CHUNKCONTAINERCOMPONENT_H

#include <unordered_set>
#include "src/engine/graphics/Graphics.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/graphics/Chunk.h"

class ChunkDrawableComponent : public DrawableComponent
{
public:
    ChunkDrawableComponent();
    ~ChunkDrawableComponent();
    void addChunk(std::shared_ptr<Chunk> chunk);
    void removeChunk(std::shared_ptr<Chunk> chunk);
    void drawSelf();


protected:
    std::unordered_set<std::shared_ptr<Chunk>> m_chunks;
};

#endif // CHUNKCONTAINERCOMPONENT_H
