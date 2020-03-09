#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "src/engine/common/GameWorld.h"
#include "src/engine/common/ui/UIElement.h"

class UIComponent : public Component
{
public:
    UIComponent();
    ~UIComponent();
    void addElement(std::string name, std::shared_ptr<UIElement> elt);
    std::shared_ptr<UIElement> getElement(std::string name);
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
    std::map<std::string, std::shared_ptr<UIElement>> m_elements;
    bool should_display;
};

#endif // UICOMPONENT_H
