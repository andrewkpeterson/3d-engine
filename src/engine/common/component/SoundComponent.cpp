#include "SoundComponent.h"

SoundComponent::SoundComponent() :
      Component()
{

}

SoundComponent::~SoundComponent()
{

}



void SoundComponent::addMusic(std::string s) {

    music.insert(std::pair<std::string, std::unique_ptr<QSoundEffect>>(s, std::make_unique<QSoundEffect>()));
    music[s]->setSource(QUrl::fromLocalFile(s.c_str()));
    music[s]->setLoopCount(1);
    music[s]->setVolume(.25);

    /*
    sounds.insert(std::pair<std::string, std::unique_ptr<QMediaPlayer>>(s, std::make_unique<QMediaPlayer>()));
    connect(sounds[], SIGNAL(positionChanrged(qint64)), this, SLOT(positionChanged(qint64)));
    sounds[s]->setMedia(QUrl::fromLocalFile(s.c_str()));
    sounds[s]->
    sounds[s]->setVolume(50);
    sounds[s]->play();
*/
}

void SoundComponent::playMusic(std::string s) {
    music[s]->play();
}

void SoundComponent::stopMusic(std::string s) {
    music[s]->stop();
}

bool SoundComponent::checkMusicIsPlaying(std::string s) {
    return music[s]->isPlaying();
}

void SoundComponent::addSound(std::string s) {
    sounds.insert(std::pair<std::string, std::unique_ptr<QSound>>(s, std::make_unique<QSound>(s.c_str())));
}

void SoundComponent::playSound(std::string s) {
    sounds[s]->play();
}

void SoundComponent::stopSound(std::string s) {
    sounds[s]->stop();
}


