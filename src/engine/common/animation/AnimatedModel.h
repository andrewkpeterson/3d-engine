#ifndef ANIMATEDMODEL_H
#define ANIMATEDMODEL_H

#include <vector>
#include <map>
#include <src/engine/common/animation/Animation.h>
#include <assimp/scene.h>
#include "src/engine/graphics/VBO.h"
#include "src/engine/graphics/VBOAttribMarker.h"
#include "src/engine/graphics/VAO.h"
#include "src/engine/common/animation/Joint.h"
#include "src/engine/graphics/Graphics.h"

class AnimatedModel
{
public:
    AnimatedModel(const aiScene *scene);
    ~AnimatedModel();

    void switchAnimation(std::string animation_name, float transition_time=ANIMATION_TRANSITION_TIME);
    void queueAnimation(std::string animation_name);
    void tick(float seconds);
    void setLocalPoseTransforms();
    void build(const aiScene *scene);
    void createMesh(const aiMesh *mesh);
    std::pair<glm::vec3, glm::vec4> createFrameInfoForJoint(std::string joint_name);
    void createAnimation(const aiAnimation *anim);
    void createJoints(const aiScene *scene);
    std::vector<std::shared_ptr<Joint>> createJointsHelper(const aiNode *node, glm::vec4 parent_pos);
    glm::mat4x4 assimpToGLM(aiMatrix4x4 &m);
    glm::vec3 assimpToGLM(aiVector3D &m);
    glm::vec4 assimpToGLM(aiQuaternion &m);
    std::shared_ptr<Animation> createTransitionAnimation(std::string next_animation, float transition_time);
    std::vector<glm::vec3> getJointBindPositions();
    std::vector<glm::vec3> getJointCurrentPosePositions();
    std::shared_ptr<Joint> getRoot();
    std::vector<glm::mat4x4> getOffsetMatrices();
    std::vector<glm::mat4x4> getInverseBindTransforms();
    std::vector<glm::mat4x4> getCurrentTotalPoseTransformations();
    void draw();
    static const constexpr float ANIMATION_TRANSITION_TIME = .1;

private:
    std::map<std::string, std::shared_ptr<Animation>> animations;
    std::map<std::string, std::shared_ptr<Joint>> joints;
    std::shared_ptr<Joint> joints_root;
    std::shared_ptr<Animation> current_animation;
    std::shared_ptr<Animation> next_animation;
    std::shared_ptr<Animation> enqueued_animation;
    GLuint m_handle;
    int num_vertices;
    float current_time;
    Graphics *g;

    const int MAX_JOINTS_PER_VERTEX = 4;
    const int POSITION_LOCATION = 0;
    const int NORMAL_LOCATION = 1;
    const int TEXC_LOCATION = 2;
    const int JOINT_ID_LOCATION = 3;
    const int JOINT_WEIGHT_LOCATION = 4;
};

#endif // ANIMATEDMODEL_H
