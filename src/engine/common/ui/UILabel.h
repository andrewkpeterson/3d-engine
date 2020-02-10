#ifndef UILABEL_H
#define UILABEL_H

#include "UI.h"
#include "UIElement.h"

class UILabel : public UIElement
{
public:
    UILabel(std::string text, float size, glm::vec3 color, glm::vec2 pos, std::string matname);
    virtual ~UILabel();

    void setText(std::string);
    void drawSelf() override;


private:
    std::string m_text;
    float m_size;
    glm::vec3 m_color;
    glm::vec2 m_pos;
    Material m_material;
    std::string m_matname;
    Graphics *g;
};

#endif // UILABEL_H
