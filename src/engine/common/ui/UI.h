#ifndef UI_H
#define UI_H

#include "src/engine/common/GameWorld.h"

class UIElement;
class UILabel;

class UI
{
public:
    UI(GameWorld *gameworld);
    ~UI();

    void drawUI();
    void addElement(std::shared_ptr<UIElement> elt);
    void resize(int width, int height);

private:
    Graphics *g;
    GameWorld *m_gameworld;
    std::shared_ptr<Camera> m_camera;
    std::vector<std::shared_ptr<UIElement>> m_elements;
};

#endif // UI_H
