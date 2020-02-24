#include "ChunkComponent.h"
#include "src/engine/common/system/ChunkStreamingSystem.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"

ChunkComponent::ChunkComponent(std::function<bool(ChunkComponent*)> build_function) :
    m_build_function(build_function),
    built(false),
    m_chunk(nullptr)
{

}

ChunkComponent::~ChunkComponent()
{

}

void ChunkComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<ChunkStreamingSystem>()->addComponent(this);
}

void ChunkComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<ChunkStreamingSystem>()->removeComponent(this);
}

void ChunkComponent::buildChunk() {
    // the chunk component passes itself into whatever its build function is (defined game-side).
    // passing in the chunk component allows the build function to make modifications to the
    // other components of the chunk's game object
    built = m_build_function(this);
    // the building function should return a boolean so that if there is some reason that the chunk was
    // not made, the gameobject can be discarded
    if (!built) {
        m_gameobject->getGameWorld()->markGameObjectForDeletion(m_gameobject->getID());
    }
}

std::shared_ptr<Chunk> ChunkComponent::getChunk() {
    return m_chunk;
}

void ChunkComponent::setChunk(std::shared_ptr<Chunk> chunk) {
    m_chunk = chunk;
}

bool ChunkComponent::isBuilt() {
    return built;
}
