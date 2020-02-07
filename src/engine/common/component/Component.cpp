#include "Component.h"

Component::Component(std::string str) :
    name(str)
{

}

Component::~Component()
{

}

const std::string Component::getName()
{
    return name;
}
