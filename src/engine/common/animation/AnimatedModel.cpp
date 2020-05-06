#include "AnimatedModel.h"
#include <assimp/scene.h>
#include <numeric>
#include <algorithm>
#include "src/engine/graphics/VBO.h"
#include "src/engine/graphics/IBO.h"
#include <iostream>
#include "JointTransform.h"

template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);
  std::stable_sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

  return idx;
}

AnimatedModel::AnimatedModel(const aiScene *scene) :
      joints_root(nullptr), current_animation(nullptr), current_time(0), next_animation(nullptr), enqueued_animation(nullptr)
{
    build(scene);
    g = Graphics::getGlobalInstance();
}

AnimatedModel::~AnimatedModel()
{

}

void AnimatedModel::queueAnimation(std::string animation_name) {
    assert(animations.find(animation_name) != animations.end());
    enqueued_animation = animations[animation_name];
    next_animation = nullptr;
}

void AnimatedModel::switchAnimation(std::string animation_name, float transition_time) {
    // interpolate between current frame of old animation and first frame of new animation, then play the new animation
    assert(animations.find(animation_name) != animations.end());
    if (current_animation != nullptr) {
        std::shared_ptr<Animation> transition_animation = createTransitionAnimation(animation_name, transition_time);
        current_animation = transition_animation;
        next_animation = animations[animation_name];
    } else {
        current_animation = animations[animation_name];
    }
    current_time = 0;
}

std::shared_ptr<Animation> AnimatedModel::createTransitionAnimation(std::string next_animation_name, float transition_time) {
    std::shared_ptr<Animation> next = animations[next_animation_name];
    std::map<std::string, std::shared_ptr<JointAnimation>> transition_animations;
    for (auto it = joints.begin(); it != joints.end(); it++) {
        std::string joint_name = it->first;
        std::vector<std::shared_ptr<KeyFrame>> keys;
        // only create a transition for a joint if that joint has keyframes for both the current animation and the next animation
        if (current_animation->getJointAnimation(joint_name) != nullptr && next->getJointAnimation(joint_name) != nullptr) {
            std::shared_ptr<KeyFrame> key1 = std::make_shared<KeyFrame>(
                current_animation->getJointAnimation(joint_name)->getPrevAndNextFrames(current_time).first->getTransform(), 0);
            std::shared_ptr<KeyFrame> key2 = std::make_shared<KeyFrame>(
                next->getJointAnimation(joint_name)->getFirstFrame()->getTransform(), transition_time);
            keys.push_back(key1);
            keys.push_back(key2);
            std::shared_ptr<JointAnimation> joint_animation = std::make_shared<JointAnimation>(keys, transition_time);
            transition_animations[joint_name] = joint_animation;
        }
    }
    std::shared_ptr<Animation> transition = std::make_shared<Animation>(transition_animations, transition_time, "transition", true);
    return transition;
}

void AnimatedModel::tick(float seconds) {
    current_time += seconds;
    if (current_time > current_animation->getTimeLength() && next_animation != nullptr && current_animation->isTransition()) {
        current_time = 0;
        current_animation = next_animation;
        next_animation = nullptr;
    } else if (current_time > current_animation->getTimeLength() && enqueued_animation != nullptr && next_animation == nullptr) {
        current_animation = enqueued_animation;
        enqueued_animation = nullptr;
        next_animation = nullptr;
        current_time = 0;
    } else if (current_time > current_animation->getTimeLength()) {
        current_time -= current_animation->getTimeLength();
    }

    setLocalPoseTransforms();
    joints_root->calcModelPoseTransform(glm::mat4x4());
}

/**
 * Get the interpolated position and quaternion for a joint in the current animation. This
 * function assumes that the joint has frames in the current animation (i.e. it acutally moves).
 */
std::pair<glm::vec3, glm::vec4> AnimatedModel::createFrameInfoForJoint(std::string joint_name) {
    std::shared_ptr<Joint> j = joints[joint_name];
    std::shared_ptr<JointAnimation> joint_anim = current_animation->getJointAnimation(joint_name);
    std::pair<std::shared_ptr<KeyFrame>, std::shared_ptr<KeyFrame>> keyframes = joint_anim->getPrevAndNextFrames(current_time);
    std::shared_ptr<KeyFrame> k1 = keyframes.first;
    std::shared_ptr<KeyFrame> k2 = keyframes.second;
    std::shared_ptr<KeyFrame> first;
    std::shared_ptr<KeyFrame> second;
    if (k1->getTimeStamp() < k2->getTimeStamp()) {
        first = k1;
        second = k2;
    } else {
        second = k1;
        first = k2;
    }
    float t = JointTransform::calculateT(first->getTimeStamp(), second->getTimeStamp(), current_time);
    glm::vec3 pos = JointTransform::positionInterpolationLinear(first->getTransform()->getPos(), second->getTransform()->getPos(), t);
    glm::vec4 quat = JointTransform::quaternionInterpolationLinear(first->getTransform()->getQuat(), second->getTransform()->getQuat(), t);
    return std::make_pair(pos, quat);
}

void AnimatedModel::setLocalPoseTransforms() {
    for (auto it = joints.begin(); it != joints.end(); it++) {
        std::shared_ptr<Joint> j = it->second;
        std::string joint_name = it->first;
        glm::mat4x4 new_local_pose_transform;
        if (current_animation->getJointAnimation(joint_name) != nullptr) {
            std::pair<glm::vec3, glm::vec4> p = createFrameInfoForJoint(joint_name);
            new_local_pose_transform = JointTransform::position2TranslationMatrix(p.first) * JointTransform::quaternion2RotationMatrix(p.second);
        } else {
            new_local_pose_transform = j->getLocalBindTransform();
        }
        j->setCurrentLocalPoseTransform(new_local_pose_transform);
    }
}

void AnimatedModel::build(const aiScene *scene) {
    createJoints(scene);

    for (int i = 0; i < scene->mNumMeshes; i++) {
        createMesh(scene->mMeshes[i]);
    }

    for (int i = 0; i < scene->mNumAnimations; i++) {
        createAnimation(scene->mAnimations[i]);
    }

    current_animation = animations["rest"];
}

void AnimatedModel::createJoints(const aiScene *scene) {
    // the root joint in the joint hierarchy MUST be a direct child of the root node of the scene,
    // and it must have the word "joint" in its name, otherwise this won't work
    int armature_index = 0;
    aiNode *nodes_root = scene->mRootNode;
    while (std::string(nodes_root->mChildren[armature_index]->mName.C_Str()).find("Armature") == std::string::npos) {
        armature_index++;
    }
    aiNode *armature_root = scene->mRootNode->mChildren[armature_index];
    aiNode *hierarchy_root = armature_root->mChildren[0];

    //aiNode *hierarchy_root = scene->mRootNode->mChildren[1];
    glm::mat4x4 mat = assimpToGLM(hierarchy_root->mTransformation);
    glm::vec4 pos = mat * glm::vec4(0,0,0,1);
    joints_root = std::make_shared<Joint>(std::string(hierarchy_root->mName.C_Str()), mat, createJointsHelper(hierarchy_root, pos), glm::vec3(pos));
    joints[std::string(hierarchy_root->mName.C_Str())] = joints_root;
    joints_root->calcInverseBindTransform(glm::mat4x4());
}

std::vector<std::shared_ptr<Joint>> AnimatedModel::createJointsHelper(const aiNode *node, glm::vec4 parent_pos) {
    std::vector<std::shared_ptr<Joint>> ret;
    for (int i = 0; i < node->mNumChildren; i++) {
        aiNode *currNode = node->mChildren[i];
        glm::mat4x4 mat = assimpToGLM(currNode->mTransformation);
        glm::vec4 pos = mat * parent_pos;
        std::shared_ptr<Joint> new_joint = std::make_shared<Joint>(std::string(currNode->mName.C_Str()), mat, createJointsHelper(currNode, pos), glm::vec3(pos));
        joints[std::string(currNode->mName.C_Str())] = new_joint;
        ret.push_back(new_joint);
    }

    return ret;
}



void AnimatedModel::createMesh(const aiMesh *mesh) {
    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<float> uvs;
    for (int i = 0; i < mesh->mNumVertices; i++) {
        positions.push_back(mesh->mVertices[i].x);
        positions.push_back(mesh->mVertices[i].y);
        positions.push_back(mesh->mVertices[i].z);

        normals.push_back(mesh->mNormals[i].x);
        normals.push_back(mesh->mNormals[i].y);
        normals.push_back(mesh->mNormals[i].z);

        //uvs.push_back(mesh->mTextureCoords[i]->x);
        //uvs.push_back(mesh->mTextureCoords[i]->y);
        uvs.push_back(0);
        uvs.push_back(0);
    }

    std::vector<int> faces;
    for (int i = 0; i < mesh->mNumFaces; i++) {
        for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
            faces.push_back(mesh->mFaces[i].mIndices[j]);
        }
    }

    std::map<std::string, int> jointname2id;
    std::map<int, std::vector<int>> vertex2joints;
    std::map<int, std::vector<float>> vertex2weights;
    std::map<int, glm::mat4x4> offset_matrices;

    for (int i = 0; i < mesh->mNumVertices; i++) {
        vertex2weights[i] = std::vector<float>();
        vertex2joints[i] = std::vector<int>();
    }

    for (int i = 0; i < mesh->mNumBones; i++) {
        jointname2id[mesh->mBones[i]->mName.C_Str()] = i;
        assert(joints.find(std::string(mesh->mBones[i]->mName.C_Str())) != joints.end());
        joints[std::string(mesh->mBones[i]->mName.C_Str())]->setID(i);
        joints[std::string(mesh->mBones[i]->mName.C_Str())]->setOffsetMatrix(assimpToGLM(mesh->mBones[i]->mOffsetMatrix));
        for (int weight_idx = 0; weight_idx < mesh->mBones[i]->mNumWeights; weight_idx++) {
            aiVertexWeight v = mesh->mBones[i]->mWeights[weight_idx];
            vertex2joints[v.mVertexId].push_back(i);
            vertex2weights[v.mVertexId].push_back(v.mWeight);
        }
    }

    std::vector<int> final_joints;
    std::vector<float> final_weights;

    for (int vert_i = 0; vert_i < mesh->mNumVertices; vert_i++) {
        assert(vertex2joints.find(vert_i) != vertex2joints.end());
        std::vector<size_t> temp = sort_indexes(vertex2weights[vert_i]);
        std::vector<int> new_joints;
        for (int k = 0; k < temp.size(); k++) {
            new_joints.push_back(0);
        }
        for (int k = 0; k < temp.size(); k++) {
            new_joints[k] = vertex2joints[vert_i][temp[k]];
        }
        std::reverse(new_joints.begin(), new_joints.end());
        std::stable_sort(vertex2weights[vert_i].begin(), vertex2weights[vert_i].end());
        std::reverse(vertex2weights[vert_i].begin(), vertex2weights[vert_i].end());
        float sum = 0;
        for (int i = 0; i < MAX_JOINTS_PER_VERTEX; i++) {
            if (i < new_joints.size()) {
                sum += vertex2weights[vert_i][i];
            }
        }
        assert(sum > 0);
        for (int i = 0; i < MAX_JOINTS_PER_VERTEX; i++) {
            if (i < new_joints.size()) {
                final_joints.push_back(new_joints[i]);
                final_weights.push_back(float(vertex2weights[vert_i][i]) / float(sum));
            } else {
                final_joints.push_back(0);
                final_weights.push_back(0);
            }
        }
    }

    num_vertices = faces.size();

    std::vector<VBOAttribMarker> posMarkers;
    posMarkers.push_back(VBOAttribMarker(POSITION_LOCATION, 3, 0));
    VBO posVBO(positions.data(), positions.size(), posMarkers, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES);

    std::vector<VBOAttribMarker> normalMarkers;
    normalMarkers.push_back(VBOAttribMarker(NORMAL_LOCATION, 3, 0));
    VBO normalVBO(normals.data(), normals.size(), normalMarkers, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES);

    std::vector<VBOAttribMarker> texMarkers;
    texMarkers.push_back(VBOAttribMarker(TEXC_LOCATION, 2, 0));
    VBO texVBO(uvs.data(), uvs.size(), texMarkers, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES);

    std::vector<VBOAttribMarker> jointMarkers;
    jointMarkers.push_back(VBOAttribMarker(JOINT_ID_LOCATION, MAX_JOINTS_PER_VERTEX, 0, VBOAttribMarker::DATA_TYPE::INT));
    VBO jointVBO(final_joints.data(), final_joints.size(), jointMarkers, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES);

    std::vector<VBOAttribMarker> weightMarkers;
    weightMarkers.push_back(VBOAttribMarker(JOINT_WEIGHT_LOCATION, MAX_JOINTS_PER_VERTEX, 0));
    VBO weightsVBO(final_weights.data(), final_weights.size(), weightMarkers, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES);

    // IBO
    IBO ibo(faces.data(), faces.size());

    // VAO
    glGenVertexArrays(1, &m_handle);
    glBindVertexArray(m_handle);

    posVBO.bindAndEnable();
    normalVBO.bindAndEnable();
    texVBO.bindAndEnable();
    jointVBO.bindAndEnable();
    weightsVBO.bindAndEnable();

    ibo.bind(); // binding the IBO before the VAO is unbound attaches the IBO to the VAO

    glBindVertexArray(0);

    posVBO.unbind();
    normalVBO.unbind();
    texVBO.unbind();
    jointVBO.unbind();
    weightsVBO.unbind();
    ibo.unbind();
}


/**
 * NOTE: This code assumes that there is always a rotation keyframe when there is a position keyframe, and
 * there is a always a position keyframe when there is a rotation keyframe. Maya appears to satisfy this condition
 * when it exports .dae files, but not when it exports .fbx files.
 * It is ok if there are no keyframes for some joints.
 */
void AnimatedModel::createAnimation(const aiAnimation *anim) {
    std::map<std::string, std::shared_ptr<JointAnimation>> joint_animations;
    for (int i = 0; i < anim->mNumChannels; i++) {
        std::vector<std::shared_ptr<KeyFrame>> keyframes;
        aiNodeAnim *channel = anim->mChannels[i];
        assert(channel->mNumPositionKeys == channel->mNumRotationKeys);
        float time = 0;
        for (int key_i = 0; key_i < channel->mNumPositionKeys; key_i++) {
            glm::vec3 pos = assimpToGLM(channel->mPositionKeys[key_i].mValue);
            glm::vec4 quat = assimpToGLM(channel->mRotationKeys[key_i].mValue);
            assert(channel->mPositionKeys[key_i].mTime - channel->mRotationKeys[key_i].mTime < .001);
            std::shared_ptr<JointTransform> j = std::make_shared<JointTransform>(pos, quat);
            time = channel->mPositionKeys[key_i].mTime;
            keyframes.push_back(std::make_shared<KeyFrame>(j,channel->mPositionKeys[key_i].mTime));
        }
        if (time < anim->mDuration - .0001) {
            int idx = channel->mNumPositionKeys - 1;
            if (idx >= 0) {
                glm::vec3 pos = assimpToGLM(channel->mPositionKeys[idx].mValue);
                glm::vec4 quat = assimpToGLM(channel->mRotationKeys[idx].mValue);
                std::shared_ptr<JointTransform> j = std::make_shared<JointTransform>(pos, quat);
                keyframes.push_back(std::make_shared<KeyFrame>(j, anim->mDuration));
            }
        }
        joint_animations[std::string(channel->mNodeName.C_Str())] = std::make_shared<JointAnimation>(keyframes, anim->mDuration);
    }

    animations[std::string(anim->mName.C_Str())] = std::make_shared<Animation>(joint_animations, anim->mDuration, std::string(anim->mName.C_Str()), false);
}

glm::mat4x4 AnimatedModel::assimpToGLM(aiMatrix4x4 &m) {
    return glm::transpose(glm::mat4x4(m.a1, m.a2, m.a3, m.a4,
                                      m.b1, m.b2, m.b3, m.b4,
                                      m.c1, m.c2, m.c3, m.c4,
                                      m.d1, m.d2, m.d3, m.d4));
}

glm::vec3 AnimatedModel::assimpToGLM(aiVector3D &v) {
    return glm::vec3(v.x,v.y,v.z);
}

glm::vec4 AnimatedModel::assimpToGLM(aiQuaternion &v) {
    return glm::vec4(v.x, v.y, v.z, v.w);
}

std::vector<glm::vec3> AnimatedModel::getJointBindPositions() {
    std::vector<glm::vec3> ret;
    for (auto it = joints.begin(); it != joints.end(); it++) {
        ret.push_back(it->second->getBindPosePosition());
    }
    return ret;
}

std::vector<glm::vec3> AnimatedModel::getJointCurrentPosePositions() {
    std::vector<glm::vec3> ret;
    for (auto it = joints.begin(); it != joints.end(); it++) {
        ret.push_back(it->second->getCurrentPosePosition());
    }
    return ret;
}

std::vector<glm::mat4x4> AnimatedModel::getOffsetMatrices() {
    std::vector<glm::mat4x4> ret;
    for (auto it = joints.begin(); it != joints.end(); it++) {
        ret.push_back(it->second->getOffsetMatrix());
    }
    return ret;
}

std::vector<glm::mat4x4> AnimatedModel::getInverseBindTransforms() {
    std::vector<glm::mat4x4> ret;
    for (auto it = joints.begin(); it != joints.end(); it++) {
        ret.push_back(it->second->getInverseBindTransform());
    }
    return ret;
}

std::vector<glm::mat4x4> AnimatedModel::getCurrentTotalPoseTransformations() {
    std::vector<glm::mat4x4> ret;
    for (auto it = joints.begin(); it != joints.end(); it++) {
        ret.push_back(it->second->getCurrentTotalPoseTransform());
    }
    return ret;
}

void AnimatedModel::draw() {
    g->setShader("animation");
    glBindVertexArray(m_handle);
    glDrawElements(GL_TRIANGLES, num_vertices, GL_UNSIGNED_INT, (const GLvoid*)0);
    //glDrawArrays(GL_TRIANGLES, )
    glBindVertexArray(0);
    g->setShader("default");
}

std::shared_ptr<Joint> AnimatedModel::getRoot() {
    return joints_root;
}


