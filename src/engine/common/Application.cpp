#include "Application.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/Screen.h"

Application::Application() :
    m_current_screen(nullptr),
    m_graphics(Graphics::getGlobalInstance()),
    app_width(1),
    app_height(1),
    m_ready_to_restart(false)
{

}

Application::~Application()
{

}

void Application::draw(Graphics *g) {
    m_current_screen->draw(g);
}

void Application::tick(float seconds) {
    if (m_ready_to_restart) {
        restart();
        m_ready_to_restart = false;
    } else {
        m_current_screen->tick(seconds);
    }
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
    //call all the restart methods on each screen
    std::map<std::string, std::shared_ptr<Screen>>::iterator it = m_screenmap.begin();
    while (it != m_screenmap.end()) {
        it->second->restartScreen();
        it++;
    }
}

void Application::changeScreen(std::string screen_name) {
    curr_screen_name = screen_name;
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
    Input::onKeyPressed(event);
}

void Application::onKeyReleased(QKeyEvent *event) {
    m_current_screen->onKeyReleased(event);
    Input::onKeyReleased(event);
}

void Application::onKeyRepeated(QKeyEvent *event) {
    m_current_screen->onKeyRepeated(event);
}

void Application::onMouseDragged(int deltaX, int deltaY) {
    m_current_screen->onMouseDragged(deltaX, deltaY);
}

void Application::onMousePressed(QMouseEvent *event) {
    m_current_screen->onMousePressed(event);
    Input::onMousePressed(event);
}

void Application::onMouseReleased(QMouseEvent *event) {
    m_current_screen->onMouseReleased(event);
    Input::onMouseReleased(event);
}

void Application::onWheelEvent(QWheelEvent *event) {
    m_current_screen->onWheelEvent(event);
}

void Application::setReadyToRestart() {
    m_ready_to_restart = true;
}

std::string Application::getCurrentScreenName() {
    return curr_screen_name;
}

glm::vec2 Application::getScreenSize() {
    return glm::vec2(app_width, app_height);
}
