#include "System.h"

System::System(GameWorld *gameworld) :
    m_gameworld(gameworld)
{

}

System::~System()
{

}

const std::string System::getName() {
    return name;
}
