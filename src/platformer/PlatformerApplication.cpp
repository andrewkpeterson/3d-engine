#include "PlatformerApplication.h"
#include "PlatformerGameplayScreen.h"
#include "PlatformerStartScreen.h"

PlatformerApplication::PlatformerApplication() :
    Application()
{
    m_screenmap["gameplay"] = std::make_shared<PlatformerGameplayScreen>(this);
    m_screenmap["start"] = std::make_shared<PlatformerStartScreen>(this);
    m_current_screen = m_screenmap["start"];
    curr_screen_name = "start";
}

PlatformerApplication::~PlatformerApplication()
{

}

void PlatformerApplication::restart() {
    Application::restart();
    m_current_screen = m_screenmap["start"];
    resize(app_width, app_height);

}
