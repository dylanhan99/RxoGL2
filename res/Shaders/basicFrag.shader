#version 330 core

//out vec4 oColor;
out vec4    o_Col;

in vec4     v_Col;
in vec2     v_TexCoord;
in float    v_TexIndex;
in float    v_IsText;

uniform sampler2D u_Textures[32];
void main()
{
	//oColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    o_Col = v_Col;
    if (v_TexIndex > 0.0)
    {
        int index = int(v_TexIndex);
        if (v_IsText > 0.5) // true
        {
            vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_Textures[index - 1], v_TexCoord).r);
            o_Col = vec4(v_Col.r, v_Col.g, v_Col.b, 1.0) * sampled;
        }
        else
        {
            //vec4 texCol = texture(u_Textures[index - 1], v_TexCoord);
            //vec4 tempCol = texCol * 0.5 + v_Col * (1 - 0.5);
            //o_Col = tempCol;
            o_Col = texture(u_Textures[index - 1], v_TexCoord);
        }
    }
}