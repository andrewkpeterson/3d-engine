#include "PlatformerStartScreenController.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/graphics/Camera.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/UIComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/Screen.h"
#include "src/engine/common/Application.h"

PlatformerStartScreenController::PlatformerStartScreenController() :
      saved_flash_time(0)

{

}

PlatformerStartScreenController::~PlatformerStartScreenController()
{

}


void PlatformerStartScreenController::tick(float seconds) {
    m_gameobject->getGameWorld()->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera()->rotate(seconds * .05,0);
    saved_flash_time += seconds;
    if (saved_flash_time > 1.3*TOTAL_FLASH_TIME) {
        saved_flash_time = 0;
    } else if (saved_flash_time > TOTAL_FLASH_TIME) {
        m_gameobject->getGameWorld()->getGameObjectByID("HUD")->getComponent<UIComponent>()->getElement("directions")->setDraw(false);
    } else {
        m_gameobject->getGameWorld()->getGameObjectByID("HUD")->getComponent<UIComponent>()->getElement("directions")->setDraw(true);
    }
    if (Input::getPressed("SPACE")) {
        m_gameobject->getGameWorld()->getScreen()->getApp()->changeScreen("gameplay");
    }
}
