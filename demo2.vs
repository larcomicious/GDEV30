/******************************************************************************
 * This is a vertex shader that assumes that each vertex has a position and
 * color. The color of the vertex is further manipulated via a uniform, and
 * this color is passed to the fragment shader as an output.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
uniform float glow;
uniform float t;
uniform vec3 color;
uniform float theta;
out vec3 shaderColor;

mat2 rotate(float angle)
{
    return mat2(
        cos(angle), -sin(angle),
        sin(angle), cos(angle)
    );
}

void main()
{
    vec2 try = vec2(vertexPosition.x, vertexPosition.y);
    vec3 a = vec3(rotate(theta)*try,vertexPosition.z);
    gl_Position = vec4(a, 1.0f);
    shaderColor = color * glow;
}
