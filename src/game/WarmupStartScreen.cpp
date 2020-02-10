#include "WarmupStartScreen.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/ui/UILabel.h"
#include "src/game/StartControlComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/component/CameraComponent.h"

WarmupStartScreen::WarmupStartScreen(Graphics *g, WarmupApplication *parent_app) :
    Screen(parent_app)
{
    initializeGameWorld();
}

WarmupStartScreen::~WarmupStartScreen()
{

}

void WarmupStartScreen::initializeGameWorld() {
    std::shared_ptr<UI> ui = std::make_shared<UI>(m_gameworld.get());
    std::shared_ptr<UILabel> label = std::make_shared<UILabel>("Press mouse to play", 80.0f, glm::vec3(1,1,1),
                                                               glm::vec2(20.0f,20.0f), "white");
    ui->addElement(label);
    m_gameworld->addUI(ui, "HUD");
    m_gameworld->setActiveUI("HUD");

    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(m_gameworld.get());
    obj->addComponent(std::make_shared<StartControlComponent>(obj.get()));
    obj->addComponent<CameraComponent>(std::make_shared<CameraComponent>(obj.get(), glm::vec3(0,0,0), glm::vec3(0,0,1)));
    m_gameworld->addGameObject(obj);
    m_gameworld->getSystem<CameraSystem>()->setCurrentMainCameraComponent(obj->getComponent<CameraComponent>().get());

}
