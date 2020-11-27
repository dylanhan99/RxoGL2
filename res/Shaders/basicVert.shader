#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}