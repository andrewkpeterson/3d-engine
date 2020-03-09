#include "DungeonApplication.h"
#include "DungeonGameplayScreen.h"
#include "DungeonStartScreen.h"
#include "DungeonPauseScreen.h"
#include "DungeonGameplayScreen.h"

DungeonApplication::DungeonApplication() :
    Application()
{
    m_screenmap["gameplay"] = std::make_shared<DungeonGameplayScreen>(this);
    m_screenmap["pause"] = std::make_shared<DungeonPauseScreen>(this);
    m_screenmap["start"] = std::make_shared<DungeonStartScreen>(this);

    m_current_screen = m_screenmap["start"];
    curr_screen_name = "start";
}

DungeonApplication::~DungeonApplication()
{

}

void DungeonApplication::restart() {
    Application::restart();
    m_current_screen = m_screenmap["gameplay"];
    resize(app_width, app_height);
}
