#include "Application.h"

Application::Application() :
    m_current_screen(nullptr),
    m_graphics(Graphics::getGlobalInstance()),
    app_width(1),
    app_height(1)
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
    //must resize all screens
    app_height = height;
    app_width = width;
    std::map<std::string, std::shared_ptr<Screen>>::iterator it = m_screenmap.begin();
    while (it != m_screenmap.end()) {
        it->second->resize(width, height);
        it++;
    }
}

void Application::restart() {
    std::map<std::string, std::shared_ptr<Screen>>::iterator it = m_screenmap.begin();
    while (it != m_screenmap.end()) {
        it->second->restartScreen();
        it++;
    }
}

void Application::changeScreen(std::string screen_name) {
    m_current_screen = m_screenmap[screen_name];
}

void Application::addScreen(std::shared_ptr<Screen> screen, std::string name) {
    m_screenmap[name] = screen;
}

void Application::removeScreen(std::string name) {
    m_screenmap.erase(name);
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
