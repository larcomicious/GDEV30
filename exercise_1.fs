/******************************************************************************
 * This is a fragment shader that simply takes a color input (coming from the
 * vertex shader) and makes it the final color of the fragment.
 *
 * Note that the color coming from the vertex shader is an interpolated value
 * coming from three vertices that make up a given triangle, which explains
 * why a gradient is created in the final image.
 *
 * Happy hacking! - eric
 *****************************************************************************/
 
#version 330 core

in vec3 shaderColor;
in vec2 anim_pass;
out vec4 fragmentColor;
uniform vec2 windowDimensions;
uniform float t;


void main()
{

    if (anim_pass.x == 1.0f) {
        fragmentColor = vec4(shaderColor, sin(t*2.5f+anim_pass.y) * 2.0f);
    } else {
        fragmentColor = vec4(shaderColor, 1.0f);
    }
    


    // vec2 centered = gl_FragCoord.xy - windowDimensions/2.0f;
    // float dist = sqrt(centered.x*centered.x + centered.y*centered.y);
    // fragmentColor = vec4(dist/50.0f, dist/50.0f,dist/50.0f, 1.0f);
}
