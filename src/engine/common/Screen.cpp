#include "Screen.h"

Screen::Screen()
{
    m_controlstates["W"] = false;
    m_controlstates["A"] = false;
    m_controlstates["S"] = false;
    m_controlstates["D"] = false;
    m_controlstates["SPACE"] = false;
    m_controlstates["MOUSE"] = false;
}

Screen::~Screen()
{

}

void Screen::onKeyPressed(QKeyEvent *event) {
    if (event->key() == Qt::Key_W) m_controlstates["W"] = true;
    if (event->key() == Qt::Key_S) m_controlstates["A"] = true;
    if (event->key() == Qt::Key_A) m_controlstates["S"] = true;
    if (event->key() == Qt::Key_D) m_controlstates["D"] = true;
    if (event->key() == Qt::Key_Space) m_controlstates["SPACE"] = true;
}

void Screen::onKeyReleased(QKeyEvent *event) {
    if (event->key() == Qt::Key_W) m_controlstates["W"] = false;
    if (event->key() == Qt::Key_S) m_controlstates["A"] = false;
    if (event->key() == Qt::Key_A) m_controlstates["S"] = false;
    if (event->key() == Qt::Key_D) m_controlstates["D"] = false;
    if (event->key() == Qt::Key_Space) m_controlstates["SPACE"] = false;
}

void Screen::onMousePressed(QKeyEvent *event) {
    m_controlstates["MOUSE"] = true;
}

void Screen::onMouseReleased(QKeyEvent *event) {
    m_controlstates["MOUSE"] = false;
}
