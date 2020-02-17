#include "ChunkDrawableComponent.h"
#include "TransformComponent.h"

ChunkDrawableComponent::ChunkDrawableComponent()
{

}

ChunkDrawableComponent::~ChunkDrawableComponent()
{

}

void ChunkDrawableComponent::drawSelf() {
    auto it = m_chunks.begin();
    while (it != m_chunks.end()) {
        std::shared_ptr<Chunk> chunk = *it;
        g->clearTransform();
        m_gameobject->getComponent<TransformComponent>()->setObjectTransform();
        chunk->draw(g);
        it++;
    }
}

void ChunkDrawableComponent::addChunk(std::shared_ptr<Chunk> chunk) {
    m_chunks.insert(chunk);
}

void ChunkDrawableComponent::removeChunk(std::shared_ptr<Chunk> chunk) {
    m_chunks.erase(chunk);
}
