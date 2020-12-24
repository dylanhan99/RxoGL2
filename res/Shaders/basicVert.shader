#version 330 core

layout(location = 0) in vec3 aPos;

//uniform mat4 pr_matrix;
//uniform mat4 vw_matrix = mat4(1.0);
//uniform mat4 ml_matrix = mat4(1.0);

layout(location = 0) in vec4    position;
layout(location = 1) in vec4    vertexColor;
layout(location = 2) in vec2    texCoord;
layout(location = 3) in float   texIndex;
layout(location = 4) in float   isText;

out vec4    v_Col;
out vec2    v_TexCoord;
out float   v_TexIndex;
out float    v_IsText;

uniform mat4 u_MVP;

void main()
{
	//gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    gl_Position = u_MVP * position;

    v_Col = vertexColor;
    v_TexCoord = texCoord;
    v_TexIndex = texIndex;
    v_IsText = isText;
}