#ifndef CHUNKCOMPONENT_H
#define CHUNKCOMPONENT_H

#include "src/engine/graphics/Chunk.h"
#include "Component.h"
#include <functional>

class ChunkComponent : public Component
{
public:
    ChunkComponent(std::function<bool(ChunkComponent*)> build_function);
    ~ChunkComponent();
    virtual void addComponentToSystemsAndConnectComponents() override;
    virtual void removeComponentFromSystems() override;

    void buildChunk();
    std::shared_ptr<Chunk> getChunk();
    void setChunk(std::shared_ptr<Chunk> chunk);
    bool isBuilt();

private:
    std::function<bool(ChunkComponent*)> m_build_function;
    bool built;
    std::shared_ptr<Chunk> m_chunk;
};

#endif // CHUNKCOMPONENT_H
