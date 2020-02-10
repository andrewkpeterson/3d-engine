#include "NPCChaseComponent.h"

NPCChaseComponent::NPCChaseComponent(GameObject *gameobject) :
    TickComponent (gameobject)
{

}

NPCChaseComponent::~NPCChaseComponent()
{

}

void NPCChaseComponent::tick(float seconds) {
    // get the player gameobject and then extract its position.
    // move toward the player
}
