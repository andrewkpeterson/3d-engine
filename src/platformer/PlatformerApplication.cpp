#include "PlatformerApplication.h"
#include "PlatformerGameplayScreen.h"

PlatformerApplication::PlatformerApplication() :
    Application()
{
    m_screenmap["gameplay"] = std::make_shared<PlatformerGameplayScreen>(this);
    m_current_screen = m_screenmap["gameplay"];
    curr_screen_name = "start";
}

PlatformerApplication::~PlatformerApplication()
{

}

void PlatformerApplication::restart() {
    Application::restart();
    m_current_screen = m_screenmap["gameplay"];
    resize(app_width, app_height);

}
