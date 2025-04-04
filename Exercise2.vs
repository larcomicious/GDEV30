/******************************************************************************
 * This is a really simple vertex shader that simply sets the output vertex's
 * position to be the same as the input.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 dirVec;
layout (location = 3) in vec2 texCoords;
out vec3 shaderColor;
out vec2 textureCoord;
out vec2 animID;
uniform float t;

mat2 rotate(float angle)
{
    return mat2(
        cos(angle), -sin(angle),
        sin(angle), cos(angle)
    );
}

void main()
{
    vec2 new_xy = vec2(vertexPosition.x/10.0f, vertexPosition.y/10.0f);

    float new_t = clamp(6 * sin(2 * 3.141592 * (-0.2 * t + 0.75)), 0, 5);
    
    gl_Position = vec4(new_xy + dirVec * new_t, 0.0f, 1.0f);
    
    shaderColor = vertexColor;
    textureCoord = texCoords;
    animID = dirVec;
}
