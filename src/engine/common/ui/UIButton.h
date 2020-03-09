#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <functional>
#include "UI.h"
#include "UIElement.h"

class UIButton : public UIElement
{
public:
    UIButton(glm::vec2 pos, std::string text, std::string font, glm::vec3 m_size, float font_size,
             std::string m_font_matname, std::string m_background_matname, std::function<void()> callback);
    ~UIButton();
    void tick(float seconds) override;
    void drawSelf() override;
    bool checkClicked();
    bool checkReleased();

private:
    std::string m_text;
    std::string m_font;
    glm::vec3 m_size;
    float m_font_size;
    glm::vec3 m_color;
    glm::vec2 m_pos;
    std::string m_font_matname;
    std::string m_backround_matname;
    Graphics *g;
    std::function<void()> m_callback;
};

#endif // UIBUTTON_H
