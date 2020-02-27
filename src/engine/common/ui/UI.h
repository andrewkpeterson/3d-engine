#ifndef UI_H
#define UI_H

#include "src/engine/common/GameWorld.h"

class UIElement;
class UILabel;

class UI
{
public:
    UI();
    ~UI();

    void drawUI();
    void addElement(std::string name, std::shared_ptr<UILabel> elt);
    std::shared_ptr<UILabel> getLabel(std::string name);
    void resize(int width, int height);
    void setGameWorld(GameWorld *gameworld);
    void setShouldDisplay(bool b);

private:
    Graphics *g;
    GameWorld *m_gameworld;
    std::shared_ptr<Camera> m_camera;
    std::map<std::string, std::shared_ptr<UILabel>> m_elements;
    bool should_display;
};

#endif // UI_H
