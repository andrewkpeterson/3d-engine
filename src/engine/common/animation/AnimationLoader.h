#ifndef ANIMATIONLOADER_H
#define ANIMATIONLOADER_H

#include <memory>
#include "Animation.h"
#include "AnimatedModel.h"

class AnimationLoader
{
public:
    AnimationLoader();
    ~AnimationLoader();
    static std::shared_ptr<AnimatedModel> loadAnimatedModel(std::string filename);
};

#endif // ANIMATIONLOADER_H
