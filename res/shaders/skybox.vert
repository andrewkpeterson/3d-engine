#version 330 core

layout (location = 0) in vec3 position;

out vec3 texc;

uniform mat4 v;
uniform mat4 p;
uniform mat4 m;

void main()
{
    texc = position;
    gl_Position = p * mat4(mat3(v)) * m * vec4(position, 1.0);
}
