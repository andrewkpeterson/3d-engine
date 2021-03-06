#ifndef INPUT_H
#define INPUT_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <map>

class Input
{
public:
    Input();
    ~Input();
    static bool getPressed(std::string);
    static void onKeyPressed(QKeyEvent *event);
    static void onKeyReleased(QKeyEvent *event);
    static void onMousePressed(QMouseEvent *event);
    static void onMouseReleased(QMouseEvent *event);
    static void restart();
    static std::map<std::string, bool> m_controlstates;
};

#endif // INPUT_H
