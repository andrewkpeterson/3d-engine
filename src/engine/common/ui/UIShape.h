#ifndef UISHAPE_H
#define UISHAPE_H

#include "UIElement.h"

class UIShape : public UIElement
{
public:
    UIShape(std::string geometry, glm::vec2 pos, glm::vec2 size, std::string matname);
    ~UIShape();

    void drawSelf() override;
    void tick(float seconds) override {}


private:
    glm::vec2 m_size;
    glm::vec2 m_pos;
    std::string m_matname;
    Graphics *g;
    std::string m_geometry;
};

#endif // UISHAPE_H
