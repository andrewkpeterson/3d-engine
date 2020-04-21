#include "Input.h"
#include <iostream>

std::map<std::string, bool> Input::m_controlstates = {{"W",false}, {"A",false}, {"S",false}, {"D",false},
                                                      {"R",false}, {"T", false}, {"SPACE",false},{"MOUSELEFT",false},
                                                      {"MOUSERIGHT",false}};

Input::Input()
{
    m_controlstates["W"] = false;
    m_controlstates["A"] = false;
    m_controlstates["S"] = false;
    m_controlstates["D"] = false;
    m_controlstates["R"] = false;
    m_controlstates["T"] = false;
    m_controlstates["SPACE"] = false;
    m_controlstates["MOUSELEFT"] = false;
    m_controlstates["MOUSERIGHT"] = false;
}

Input::~Input()
{

}

bool Input::getPressed(std::string str) {
    return m_controlstates[str];
}

void Input::onKeyPressed(QKeyEvent *event) {
    if (event->key() == Qt::Key_W) m_controlstates["W"] = true;
    if (event->key() == Qt::Key_S) m_controlstates["S"] = true;
    if (event->key() == Qt::Key_A) m_controlstates["A"] = true;
    if (event->key() == Qt::Key_D) m_controlstates["D"] = true;
    if (event->key() == Qt::Key_R) m_controlstates["R"] = true;
    if (event->key() == Qt::Key_T) m_controlstates["T"] = true;
    if (event->key() == Qt::Key_Space) m_controlstates["SPACE"] = true;
}

void Input::onKeyReleased(QKeyEvent *event) {
    if (event->key() == Qt::Key_W) m_controlstates["W"] = false;
    if (event->key() == Qt::Key_S) m_controlstates["S"] = false;
    if (event->key() == Qt::Key_A) m_controlstates["A"] = false;
    if (event->key() == Qt::Key_D) m_controlstates["D"] = false;
    if (event->key() == Qt::Key_R) m_controlstates["R"] = false;
    if (event->key() == Qt::Key_T) m_controlstates["T"] = false;
    if (event->key() == Qt::Key_Space) m_controlstates["SPACE"] = false;
}

void Input::restart() {
    m_controlstates["W"] = false;
    m_controlstates["A"] = false;
    m_controlstates["S"] = false;
    m_controlstates["D"] = false;
    m_controlstates["R"] = false;
    m_controlstates["T"] = false;
    m_controlstates["SPACE"] = false;
    m_controlstates["MOUSELEFT"] = false;
    m_controlstates["MOUSERIGHT"] = false;
}

void Input::onMousePressed(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_controlstates["MOUSELEFT"] = true;
    } else if (event->button() == Qt::RightButton) {
        m_controlstates["MOUSERIGHT"] = true;
    }
}

void Input::onMouseReleased(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_controlstates["MOUSELEFT"] = false;
    } else if (event->button() == Qt::RightButton) {
        m_controlstates["MOUSERIGHT"] = false;
    }
}
