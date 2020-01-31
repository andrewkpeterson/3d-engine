#include "Application.h"

Application::Application() :
    m_current_screen(nullptr)
{

}

Application::~Application()
{

}

void Application::draw(Graphics *g) {
    m_current_screen->draw(g);
}

void Application::tick(float seconds) {
    m_current_screen->tick(seconds);
}

void Application::resize(int width, int height) {
    m_current_screen->resize(width, height);
}

void Application::onKeyPressed(QKeyEvent *event) {
    m_current_screen->onKeyPressed(event);
}

void Application::onKeyReleased(QKeyEvent *event) {
    m_current_screen->onKeyReleased(event);
}

void Application::onKeyRepeated(QKeyEvent *event) {
    m_current_screen->onKeyRepeated(event);
}

void Application::onMouseDragged(int deltaX, int deltaY) {
    m_current_screen->onMouseDragged(deltaX, deltaY);
}

void Application::onMousePressed(QMouseEvent *event) {
    m_current_screen->onMousePressed(event);
}

void Application::onMouseReleased(QMouseEvent *event) {
    m_current_screen->onMouseReleased(event);
}

void Application::onWheelEvent(QWheelEvent *event) {
    m_current_screen->onWheelEvent(event);
}
