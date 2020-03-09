#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <functional>
#include "UI.h"
#include "UIElement.h"

class UIButton
{
public:
    UIButton();
    ~UIButton();
    void tick(float seconds);
    void checkClicked();
    void checkReleased();

private:
    std::string m_text;
    float m_size;
    glm::vec3 m_color;
    glm::vec2 m_pos;
    std::string m_material;
    std::string m_matname;
    Graphics *g;
    std::string m_font;
    std::function<void()> callback;
};

#endif // UIBUTTON_H
