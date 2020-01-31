#include "WarmupApplication.h"
#include "WarmupGameplayScreen.h"
#include "WarmupStartScreen.h"

WarmupApplication::WarmupApplication(Graphics *g) :
    Application()
{
    m_screenmap["start"] = std::make_shared<WarmupStartScreen>();
    m_screenmap["gameplay"] = std::make_shared<WarmupGameplayScreen>(g);

    m_current_screen = m_screenmap["gameplay"];
}

WarmupApplication::~WarmupApplication()
{

}

void WarmupApplication::startScreenToGameplayScreen() {
    m_current_screen = m_screenmap["gameplay"];
}

void WarmupApplication::restart() {
    m_current_screen = m_screenmap["start"];
}
