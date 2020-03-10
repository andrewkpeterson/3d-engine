#ifndef UICONTROLLERCOMPONENT_H
#define UICONTROLLERCOMPONENT_H

#include "src/engine/common/component/ControlCallbackComponent.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/Screen.h"

class UIControllerComponent : public ControlCallbackComponent
{
public:
    UIControllerComponent(std::string cursor_geometry, std::string cursor_matname, glm::vec3 cursor_size,
                          glm::vec3 cursor_picture_offset);
    ~UIControllerComponent();
    void addComponentToSystemsAndConnectComponents() override;
    void removeComponentFromSystems() override;

    void onKeyPressed(QKeyEvent *event) override;
    void onKeyReleased(QKeyEvent *event) override;
    void onKeyRepeated(QKeyEvent *event) override;
    void onMousePressed(QMouseEvent *event) override;
    void onMouseReleased(QMouseEvent *event) override;
    void onMouseDragged(int deltaX, int deltaY) override;
    void onWheelEvent(QWheelEvent *event) override;
    void tick(float seconds) override;
    void drawCursor();

    bool getMousePressed();

private:
    std::string m_cursor_geometry;
    std::string m_cursor_matname;
    glm::vec3 m_cursor_size;
    bool m_mouse_pressed;
    Graphics *g;
    glm::vec2 m_cursor_picture_offset;
};

#endif // UICONTROLLERCOMPONENT_H
