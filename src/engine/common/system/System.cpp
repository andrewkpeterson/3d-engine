#include "System.h"

System::System(std::string str, std::shared_ptr<GameWorld> gameworld) :
    m_gameworld(gameworld),
    name(str)
{

}

System::~System()
{

}

const std::string System::getName() {
    return name;
}
