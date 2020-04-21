#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include <QSoundEffect>
#include <map>
#include "Component.h"
#include <QUrl>
#include <QMediaPlayer>

class SoundComponent : public Component
{
public:
    SoundComponent();
    ~SoundComponent();
    virtual void addComponentToSystemsAndConnectComponents() {}
    virtual void removeComponentFromSystems() {}
    void addSound(std::string s);
    void stopSound(std::string s);
    void playSound(std::string s);

private:
    std::map<std::string, std::unique_ptr<QSoundEffect>> sounds;
};

#endif // SOUNDCOMPONENT_H
