#ifndef UILABEL_H
#define UILABEL_H

#include "UI.h"
#include "UIElement.h"

class UILabel : public UIElement
{
public:
    UILabel(UIComponent *component, std::string text, float size, glm::vec3 color,
            glm::vec2 pos, std::string matname, std::string font);
    virtual ~UILabel();

    void setText(std::string);
    void drawSelf() override;
    void tick(float seconds) override {}


private:
    std::string m_text;
    float m_size;
    glm::vec3 m_color;
    glm::vec2 m_pos;
    std::string m_matname;
    Graphics *g;
    std::string m_font;
};

#endif // UILABEL_H
