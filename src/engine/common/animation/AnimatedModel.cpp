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
      joints_root(nullptr), current_animation(nullptr), current_time(0)
{
    build(scene);
    g = Graphics::getGlobalInstance();
}

AnimatedModel::~AnimatedModel()
{

}

void AnimatedModel::switchAnimation(std::string animation_name) {
    // interpolate between current frame of old animation and first frame of new animation, then play the new animation
    current_animation = animations[animation_name];
    current_time = 0;
}

void AnimatedModel::tick(float seconds) {
    current_time += seconds;
    if (current_time > current_animation->getTimeLength()) {
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
    int count = 0;
    for (auto it = joints.begin(); it != joints.end(); it++) {
        std::shared_ptr<Joint> j = it->second;
        std::string joint_name = it->first;
        glm::mat4x4 new_local_pose_transform;
        if (current_animation->getJointAnimation(joint_name) != nullptr) {
            std::pair<glm::vec3, glm::vec4> p = createFrameInfoForJoint(joint_name);
            count++;
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

    current_animation = animations.begin()->second;
}

void AnimatedModel::createJoints(const aiScene *scene) {
    // the root joint in the joint hierarchy MUST be a direct child of the root node of the scene,
    // and it must have the word "joint" in its name, otherwise this won't work
    int idx = 0;
    aiNode *currNode = scene->mRootNode->mChildren[idx];
    while (idx < scene->mRootNode->mNumChildren) {
        currNode = scene->mRootNode->mChildren[idx];
        if (std::string(currNode->mName.C_Str()).find("joint") != std::string::npos) {
            joints_root = std::make_shared<Joint>(std::string(currNode->mName.C_Str()),
                                                  assimpToGLM(currNode->mTransformation), createJointsHelper(currNode));
            joints[std::string(currNode->mName.C_Str())] = joints_root;
        }
        idx++;
    }

    joints_root->calcInverseBindTransform(glm::mat4x4());
}

std::vector<std::shared_ptr<Joint>> AnimatedModel::createJointsHelper(const aiNode *node) {
    std::vector<std::shared_ptr<Joint>> ret;
    for (int i = 0; i < node->mNumChildren; i++) {
        aiNode *currNode = node->mChildren[i];
        std::shared_ptr<Joint> new_joint = std::make_shared<Joint>(std::string(currNode->mName.C_Str()),
                                                                   assimpToGLM(currNode->mTransformation), createJointsHelper(currNode));
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
        uvs.push_back(.5);
        uvs.push_back(.5);
    }

    std::vector<int> faces;
    for (int i = 0; i < mesh->mNumFaces; i++) {
        faces.push_back(mesh->mFaces[i].mIndices[0]);
        faces.push_back(mesh->mFaces[i].mIndices[1]);
        faces.push_back(mesh->mFaces[i].mIndices[2]);
    }

    std::map<std::string, int> jointname2id;
    std::map<int, std::vector<float>> joint_weights;
    std::map<int, std::vector<int>> vertex2joints;
    std::map<int, std::vector<float>> vertex2weights;
    std::map<int, glm::mat4x4> offset_matrices;

    for (int i = 0; i < mesh->mNumBones; i++) {
        jointname2id[mesh->mBones[i]->mName.C_Str()] = i;
        joints[std::string(mesh->mBones[i]->mName.C_Str())]->setID(i);
        joint_weights[i] = std::vector<float>();
        offset_matrices[i] = assimpToGLM(mesh->mBones[i]->mOffsetMatrix);
        for (int weight_idx = 0; weight_idx < mesh->mBones[i]->mNumWeights; weight_idx++) {
            aiVertexWeight v = mesh->mBones[i]->mWeights[weight_idx];
            vertex2joints[v.mVertexId].push_back(i);
            vertex2weights[v.mVertexId].push_back(v.mWeight);
        }
    }

    std::vector<int> final_joints;
    std::vector<float> final_weights;
    for (int vert_i = 0; vert_i < mesh->mNumVertices; vert_i++) {
        if (vertex2joints.find(vert_i) != vertex2joints.end()) {
            std::vector<size_t> temp = sort_indexes(vertex2weights[vert_i]);
            for (int k = 0; k < temp.size(); k++) {
                vertex2joints[vert_i][k] = temp[k];
            }
            std::reverse(vertex2joints[vert_i].begin(), vertex2joints[vert_i].end());
            std::stable_sort(vertex2weights[vert_i].begin(), vertex2weights[vert_i].end());
            std::reverse(vertex2weights[vert_i].begin(), vertex2weights[vert_i].end());
            float sum = 0;
            for (int i = 0; i < MAX_JOINTS_PER_VERTEX; i++) {
                if (i < vertex2joints[vert_i].size()) {
                    sum += vertex2weights[vert_i][i];
                } else {
                    sum += 0;
                }
            }
            if (sum > 0) {
                for (int i = 0; i < MAX_JOINTS_PER_VERTEX; i++) {
                    if (i < vertex2joints[vert_i].size()) {
                        final_joints.push_back(vertex2joints[vert_i][i]);
                        final_weights.push_back(vertex2weights[vert_i][i] / sum);
                    } else {
                        final_joints.push_back(0);
                        final_weights.push_back(0);
                    }
                }
            } else {
                for (int i = 0; i < MAX_JOINTS_PER_VERTEX; i++) {
                    final_joints.push_back(0);
                    final_weights.push_back(0);
                }
            }
        } else {
            for (int i = 0; i < MAX_JOINTS_PER_VERTEX; i++) {
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
    jointMarkers.push_back(VBOAttribMarker(JOINT_ID_LOCATION, 4, 0, VBOAttribMarker::DATA_TYPE::INT));
    VBO jointVBO(final_joints.data(), final_joints.size(), jointMarkers, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES);

    std::vector<VBOAttribMarker> weightMarkers;
    weightMarkers.push_back(VBOAttribMarker(JOINT_WEIGHT_LOCATION, 4, 0));
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

    animations[std::string(anim->mName.C_Str())] = std::make_shared<Animation>(joint_animations, anim->mDuration, std::string(anim->mName.C_Str()));
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

void AnimatedModel::draw() {
    g->setShader("animation");
    glBindVertexArray(m_handle);
    glDrawElements(GL_TRIANGLES, num_vertices, GL_UNSIGNED_INT, (const GLvoid*)0);
    glBindVertexArray(0);
    g->setShader("default");
}


