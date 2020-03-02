#include "DungeonAttackAction.h"

DungeonAttackAction::DungeonAttackAction(Component *component) :
    Action(component)
{

}

DungeonAttackAction::~DungeonAttackAction()
{

}

void DungeonAttackAction::reset() {

}

Status DungeonAttackAction::update(float seconds) {
    std::cout << "Enemy attacked" << std::endl;
    return FAIL;
}
