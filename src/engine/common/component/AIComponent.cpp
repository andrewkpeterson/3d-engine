#include "AIComponent.h"

AIComponent::AIComponent()
{

}

AIComponent::~AIComponent()
{

}

void AIComponent::tick(float seconds) {
    bt_root->update(seconds);
}
