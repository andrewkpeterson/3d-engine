#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "src/engine/common/GameWorld.h"
#include "src/engine/common/ui/UIElement.h"

class UIComponent : public Component
{
public:
    UIComponent();
    ~UIComponent();
    void drawUI();
    void addElement(std::string name, std::shared_ptr<UILabel> elt);
    std::shared_ptr<UILabel> getLabel(std::string name);
    void resize(int width, int height);
    void setGameWorld(GameWorld *gameworld);
    void setShouldDisplay(bool b);
    void drawSelf();
    void tick(float seconds);
    virtual void addComponentToSystemsAndConnectComponents() override;
    virtual void removeComponentFromSystems() override;

private:
    Graphics *g;
    GameWorld *m_gameworld;
    std::shared_ptr<Camera> m_camera;
    std::map<std::string, std::shared_ptr<UILabel>> m_elements;
    bool should_display;
};

#endif // UICOMPONENT_H
