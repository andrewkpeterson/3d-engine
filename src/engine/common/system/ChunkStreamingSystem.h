#ifndef CHUNKSTREAMINGSYSTEM_H
#define CHUNKSTREAMINGSYSTEM_H

#include <queue>
#include <set>
#include "src/engine/common/system/System.h"
#include "src/engine/common/component/ChunkComponent.h"
#include "src/engine/graphics/Chunk.h"

class ChunkStreamingSystem : public System
{
public:
    ChunkStreamingSystem(GameWorld *gameworld);
    ~ChunkStreamingSystem();

    void buildEnqueuedChunk();
    void buildAllEnqueuedChunks();
    void destroyBuiltChunk();
    void addComponent(ChunkComponent *component);
    void removeComponent(ChunkComponent *component);

private:
    std::set<ChunkComponent*> chunks_to_build;
    std::unordered_set<ChunkComponent*> built_chunks;
};

#endif // CHUNKSTREAMINGSYSTEM_H
