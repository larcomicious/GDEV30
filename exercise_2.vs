/******************************************************************************
 * This is a really simple vertex shader that simply sets the output vertex's
 * position to be the same as the input.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexTexCoord;
out vec3 shaderColor;
out vec2 shaderTexCoord;
uniform float t;
uniform float theta;

mat2 rotate(float angle)
{
    return mat2(
        cos(angle), -sin(angle),
        sin(angle), cos(angle)
    );
}

void main()
{
    // vec2 temp = vec2(vertexPosition.x *(16/9), vertexPosition.y) * rotate(theta);
    vec2 temp = vec2(vertexPosition.x *(16/9), vertexPosition.y);
    gl_Position = vec4(temp, vertexPosition.z, 1.0f) * t;
    shaderColor = vertexColor;
    shaderTexCoord = vertexTexCoord;
}
