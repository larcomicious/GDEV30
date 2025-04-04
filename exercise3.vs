/******************************************************************************
 * This is a really simple vertex shader that simply sets the output vertex's
 * position to be the same as the input.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;

uniform mat4 matrix;
out vec3 shaderColor;
out vec3 barycoord;
out vec2 shaderTexCoord;

void main()
{
    gl_Position = matrix * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0f);
    shaderColor = vertexColor;
    shaderTexCoord = vec2(gl_Position.x*1.5f, gl_Position.y*1.5f);

    if ((gl_VertexID%3) == 0) {
        barycoord = vec3(1.0f, 0.0f, 0.0f);
    } else if ((gl_VertexID%3) == 1) {
        barycoord = vec3(0.0f, 1.0f, 0.0f);
    } else {
        barycoord = vec3(0.0f, 0.0f, 1.0f);
    }
}

