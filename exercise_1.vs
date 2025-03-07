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
layout (location = 2) in float rotSpeed;
layout (location = 3) in vec2 anim_info;
uniform float glow;
uniform float t;
uniform float percent;
uniform int shift;
uniform vec2 windowDimensions;
vec3 cur_color;
vec3 next_color;
out vec3 shaderColor;
out vec2 anim_pass;

mat2 rotate(float angle)
{
    return mat2(
        cos(angle), -sin(angle),
        sin(angle), cos(angle)
    );
}

void main()
{
    vec2 new_vertex;
    if (anim_info.x == 2) {
        vec2 translated = vec2(vertexPosition.xy) - vec2(-360, -150); // move to origin
        translated = translated * rotate(t * rotSpeed); // rotate
        new_vertex = translated + vec2(-360, -150);
    }
    else if (anim_info.x == 3) {
        vec2 translated = vec2(vertexPosition.xy) - vec2(360, -150); // move to origin
        translated = translated * rotate(t * rotSpeed); // rotate
        new_vertex = translated + vec2(360, -150);
    }
    else {
        new_vertex = vec2(vertexPosition.xy) * rotate(t * rotSpeed);
    }

    vec3 start, end;
    vec3 cur_color = mix(start, end, (sin(t)+1.0)/2.0);
    gl_Position = vec4((new_vertex.x/(windowDimensions.x/2)), (new_vertex.y/(windowDimensions.y/2)), 0.0f, 1.0f);
    shaderColor = vertexColor;
    anim_pass = anim_info;

}
