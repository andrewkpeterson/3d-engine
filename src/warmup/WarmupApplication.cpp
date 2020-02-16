#include "WarmupApplication.h"
#include "WarmupGameplayScreen.h"
#include "WarmupStartScreen.h"

WarmupApplication::WarmupApplication() :
    Application()
{
    m_screenmap["start"] = std::make_shared<WarmupStartScreen>(this);
    m_screenmap["gameplay"] = std::make_shared<WarmupGameplayScreen>(this);

    m_current_screen = m_screenmap["start"];
}

WarmupApplication::~WarmupApplication()
{

}

void WarmupApplication::restart() {
    Application::restart();
    m_current_screen = m_screenmap["start"];
    resize(app_width, app_height);
}
