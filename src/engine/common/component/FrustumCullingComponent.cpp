#include "FrustumCullingComponent.h"

FrustumCullingComponent::FrustumCullingComponent() :
    ChunkDrawableComponent ()
{

}

FrustumCullingComponent::~FrustumCullingComponent()
{

}

void FrustumCullingComponent::drawSelf() {
    // get current camera of the gameworld

    // test camera view volume against chunks

    // draw the chunks that pass the test
}
