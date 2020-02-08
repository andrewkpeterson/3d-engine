#include "ControlCallbackSystem.h"

ControlCallbackSystem::ControlCallbackSystem(std::shared_ptr<GameWorld> gameworld) :
    System("ControlCallbackSystem", gameworld)
{

}

ControlCallbackSystem::~ControlCallbackSystem()
{

}

void ControlCallbackSystem::onKeyPressed(QKeyEvent *event) {
}

void ControlCallbackSystem::onKeyReleased(QKeyEvent *event) {
}

void ControlCallbackSystem::onKeyRepeated(QKeyEvent *event) {
}

void ControlCallbackSystem::onMousePressed(QMouseEvent *event) {
}

void ControlCallbackSystem::onMouseReleased(QMouseEvent *event) {
}

void ControlCallbackSystem::onMouseDragged(int deltaX, int deltaY) {
}

void ControlCallbackSystem::onWheelEvent(QWheelEvent *event) {
}
