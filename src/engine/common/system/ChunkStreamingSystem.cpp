#include "ChunkStreamingSystem.h"
#include "CameraSystem.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/component/TransformComponent.h"

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
        built_chunks.insert(chunk);
    }
}

void ChunkStreamingSystem::buildAllEnqueuedChunks() {
    auto it = chunks_to_build.begin();
    while (it != chunks_to_build.end()) {
        ChunkComponent* chunk = *it;
        chunk->buildChunk();
        built_chunks.insert(chunk);
        it++;
    }
    chunks_to_build.clear();
}

void ChunkStreamingSystem::destroyOldChunksOutsideRadius() { // the game side tells the engine when to get rid of chunks
    // go through chunks
    auto it = built_chunks.begin();
    glm::vec3 eye = m_gameworld->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera()->getEye();
    while(it != built_chunks.end()) {
        // figure out which ones can be destroyed using the current camera
        ChunkComponent *chunk_comp = *it;
        if (glm::length(eye - chunk_comp->getGameObject()->getComponent<TransformComponent>()->getPos()) > CHUNK_RADIUS) {
            std::cout << "chunk deleted" << std::endl;
            m_gameworld->markGameObjectForDeletion(chunk_comp->getGameObject()->getID());
        }
        it++;
    }
}

void ChunkStreamingSystem::destroyChunksBehindZValue(float z) {
    auto it = built_chunks.begin();
    while(it != built_chunks.end()) {
        ChunkComponent *chunk_comp = *it;
        if (chunk_comp->getGameObject()->getComponent<TransformComponent>()->getPos().z - z < 0) {
            //std::cout << "chunk deleted" << std::endl;
            m_gameworld->markGameObjectForDeletion(chunk_comp->getGameObject()->getID());
        }
        it++;
    }
}

void ChunkStreamingSystem::destroyChunksBeyondZValue(float z) {
    auto it = built_chunks.begin();
    while(it != built_chunks.end()) {
        ChunkComponent *chunk_comp = *it;
        if (chunk_comp->getGameObject()->getComponent<TransformComponent>()->getPos().z - z > 0) {
            //std::cout << "chunk deleted" << std::endl;
            m_gameworld->markGameObjectForDeletion(chunk_comp->getGameObject()->getID());
        }
        it++;
    }
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
