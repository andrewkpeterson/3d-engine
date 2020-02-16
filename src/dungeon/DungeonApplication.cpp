#include "DungeonApplication.h"
#include "DungeonGameplayScreen.h"

DungeonApplication::DungeonApplication() :
    Application()
{
    m_screenmap["gameplay"] = std::make_shared<DungeonGameplayScreen>(this);

    m_current_screen = m_screenmap["gameplay"];
}

DungeonApplication::~DungeonApplication()
{

}

void DungeonApplication::restart() {
    Application::restart();
    m_current_screen = m_screenmap["gamplay"];
    resize(app_width, app_height);
}
