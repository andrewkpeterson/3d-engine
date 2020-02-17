#ifndef DUNGEONENVIRONMENTCOMPONENT_H
#define DUNGEONENVIRONMENTCOMPONENT_H

#include "src/engine/graphics/Chunk.h"
#include "src/engine/common/component/ChunkDrawableComponent.h"
#include "src/engine/common/component/Component.h"
#include "src/dungeon/environment/DungeonEnvironmentData.h"
#include "src/engine/common/map/MapGenerator.h"
#include "src/engine/common/component/TickComponent.h"

class DungeonEnvironmentComponent : public TickComponent
{
public:
    DungeonEnvironmentComponent();
    ~DungeonEnvironmentComponent();

    virtual void addComponentToSystemsAndConnectComponents() override;
    virtual void removeComponentFromSystems() override;
    void makeDungeonChunksFromMapSegment(std::shared_ptr<MapSegment> seg);
    void makeChunk(std::shared_ptr<MapSegment> seg, int startrow, int startcol);
    void tick(float seconds);

private:
    const int DUNGEON_CHUNK_SIZE = 5;
};

#endif // DUNGEONENVIRONMENTCOMPONENT_H
