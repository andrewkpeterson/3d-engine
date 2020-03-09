#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "UI.h"
#include "UIElement.h"

class UIButton
{
public:
    UIButton();
    ~UIButton();
    void tick(float seconds);
    void checkClicked();

private:
    std::string m_text;
    float m_size;
    glm::vec3 m_color;
    glm::vec2 m_pos;
    std::string m_material;
    std::string m_matname;
    Graphics *g;
    std::string m_font;
};

#endif // UIBUTTON_H
