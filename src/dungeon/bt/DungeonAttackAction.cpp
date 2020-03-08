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
    return SUCCESS;
}
