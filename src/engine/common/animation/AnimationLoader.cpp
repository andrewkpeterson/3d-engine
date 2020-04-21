#include "AnimationLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <QString>

AnimationLoader::AnimationLoader()
{

}

AnimationLoader::~AnimationLoader()
{

}

std::shared_ptr<AnimatedModel> AnimationLoader::loadAnimatedModel(std::string filename) {
    Assimp::Importer importer;
    QString string = QString(PROJECT_PATH) + QString(filename.c_str());
    const aiScene *scene = importer.ReadFile(string.toStdString(), aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene) {
        std::cout << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    return std::make_shared<AnimatedModel>(scene);
}
