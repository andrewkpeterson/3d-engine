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

void Application::onKeyPressed(QKeyEvent *event) {
    m_current_screen->onKeyPressed(event);
}

void Application::onKeyReleased(QKeyEvent *event) {
    m_current_screen->onKeyReleased(event);
}

void Application::onMouseDragged(QKeyEvent *event) {
    m_current_screen->onMouseDragged(event);
}

void Application::onMousePressed(QKeyEvent *event) {
    m_current_screen->onMousePressed(event);
}

void Application::onMouseReleased(QKeyEvent *event) {
    m_current_screen->onMouseReleased(event);
}

void Application::onWheelEvent(QKeyEvent *event) {
    m_current_screen->onWheelEvent(event);
}
