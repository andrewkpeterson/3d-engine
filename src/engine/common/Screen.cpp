#include "Screen.h"

Screen::Screen(Application *parent) :
    m_parent(parent),
    m_gameworld(std::make_shared<GameWorld>(this))
{

}

Screen::~Screen()
{

}

void Screen::tick(float seconds) {
    m_gameworld->tick(seconds);
}

void Screen::draw(Graphics *g) {
    m_gameworld->draw(g);
}

void Screen::resize(int width, int height) {
    m_gameworld->resize(width, height);
}

void Screen::onKeyPressed(QKeyEvent *event) {
    m_gameworld->onKeyPressed(event);
}

void Screen::onKeyReleased(QKeyEvent *event) {
    m_gameworld->onKeyReleased(event);
}

void Screen::onKeyRepeated(QKeyEvent *event) {
    m_gameworld->onKeyRepeated(event);
}

void Screen::restartScreen() {
    initializeGameWorld();
}

void Screen::onMousePressed(QMouseEvent *event) {
    m_gameworld->onMousePressed(event);
}

void Screen::onMouseReleased(QMouseEvent *event) {
    m_gameworld->onMouseReleased(event);
}

void Screen::onMouseDragged(int deltaX, int deltaY) {
    m_gameworld->onMouseDragged(deltaX, deltaY);
}

void Screen::onWheelEvent(QWheelEvent *event) {
    m_gameworld->onWheelEvent(event);
}
