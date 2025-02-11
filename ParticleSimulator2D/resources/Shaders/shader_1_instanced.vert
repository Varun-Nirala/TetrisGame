#version 460 core

layout (location = 0) in vec4 vertex;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vertex;
}