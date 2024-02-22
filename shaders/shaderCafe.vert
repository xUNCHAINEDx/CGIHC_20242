#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec4 vColor;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(pos, 1.0f);
    vColor = vec4(0.478f, 0.255f, 0.067f, 1.0f); // Caf�
}