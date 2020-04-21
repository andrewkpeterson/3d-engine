#version 330 core

layout(location = 0) in vec3 position; // Position of the vertex
layout(location = 1) in vec3 normal;   // Normal of the vertex
layout(location = 2) in vec2 texCoord; // UV texture coordinates
layout(location = 3) in ivec4 joint_ids;
layout(location = 4) in vec4 joint_weights;

const int MAX_JOINTS = 100;
const int JOINTS_PER_VERTEX = 4;

uniform mat4 m;
uniform mat4 joints[MAX_JOINTS];
uniform mat4 v;
uniform mat4 p;

out vec4 normal_worldSpace;
out vec4 position_worldSpace;
out vec4 eye_worldSpace;
out vec2 texc;
out float outfloat;

void main(){

    mat4 joint_transform = joints[joint_ids[0]] * joint_weights[0];
    joint_transform += joints[joint_ids[1]] * joint_weights[1];
    joint_transform += joints[joint_ids[2]] * joint_weights[2];
    joint_transform += joints[joint_ids[3]] * joint_weights[3];


    /*
    mat4 joint_transform = mat4(1,0,0,0,
                                0,1,0,0,
                                0,0,1,0,
                                0,0,0,1);
                                */
    outfloat = 1;


    texc = texCoord;
    position_worldSpace = m * joint_transform * vec4(position, 1.0);
    normal_worldSpace = vec4(normalize(mat3(transpose(inverse(m * joint_transform))) * normal), 0);
    eye_worldSpace = inverse(v)*vec4(0,0,0,1);
    gl_Position = p * v * m * joint_transform * vec4(position, 1.0);
}
