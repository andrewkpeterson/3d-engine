#include "ChunkStreamingSystem.h"

ChunkStreamingSystem::ChunkStreamingSystem(GameWorld *gameworld) :
    System(gameworld)
{

}

ChunkStreamingSystem::~ChunkStreamingSystem()
{

}

void ChunkStreamingSystem::buildEnqueuedChunk() {
    if (chunks_to_build.size() > 0) {
        ChunkComponent* chunk = *chunks_to_build.begin();
        chunks_to_build.erase(chunk);
        chunk->buildChunk();
    }
}

void ChunkStreamingSystem::buildAllEnqueuedChunks() {
    auto it = chunks_to_build.begin();
    while (it != chunks_to_build.end()) {
        ChunkComponent* chunk = *it;
        chunk->buildChunk();
        it++;
    }
    chunks_to_build.clear();
}

void ChunkStreamingSystem::destroyBuiltChunk() {
    // go through chunks
    // figure out which ones can be destroyed using the current camera
    // destroy a chunk that can be destroyed (i.e. remove the gameobject of that chunk from the gameworld)
}

void ChunkStreamingSystem::addComponent(ChunkComponent *component) {
    chunks_to_build.insert(component);
}

void ChunkStreamingSystem::removeComponent(ChunkComponent *component) {
    // if the chunk is built, then remove it from the unordered set of build chunks, otherwise remove it from the set of unbuilt chunks
    if (built_chunks.find(component) != built_chunks.end()) {
        built_chunks.erase(component);
    } else {
        chunks_to_build.erase(component);
    }
}
