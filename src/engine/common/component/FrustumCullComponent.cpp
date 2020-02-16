#include "FrustumCullComponent.h"

FrustumCullComponent::FrustumCullComponent() :
    DrawableComponent ("chunks", )
{

}

FrustumCullComponent::~FrustumCullComponent()
{

}

void FrustumCullComponent::drawSelf() {
    // get current camera of the gameworld

    // test camera view volume against chunks in chunk component

    // draw the chunk that pass the test
}
