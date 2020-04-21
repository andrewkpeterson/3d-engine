#include "SoundComponent.h"

SoundComponent::SoundComponent() :
      Component()
{

}

SoundComponent::~SoundComponent()
{

}



void SoundComponent::addSound(std::string s) {

    sounds.insert(std::pair<std::string, std::unique_ptr<QSoundEffect>>(s, std::make_unique<QSoundEffect>()));
    sounds[s]->setSource(QUrl::fromLocalFile(s.c_str()));
    sounds[s]->setLoopCount(1);
    sounds[s]->setVolume(.25);

    /*
    sounds.insert(std::pair<std::string, std::unique_ptr<QMediaPlayer>>(s, std::make_unique<QMediaPlayer>()));
    connect(sounds[], SIGNAL(positionChanrged(qint64)), this, SLOT(positionChanged(qint64)));
    sounds[s]->setMedia(QUrl::fromLocalFile(s.c_str()));
    sounds[s]->
    sounds[s]->setVolume(50);
    sounds[s]->play();
*/
}

void SoundComponent::playSound(std::string s) {
    sounds[s]->play();
}

void SoundComponent::stopSound(std::string s) {
    sounds[s]->stop();
}
