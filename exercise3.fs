/******************************************************************************
 * This is a really simple fragment shader that simply sets the output fragment
 * color to yellow.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

in vec3 shaderColor;
in vec3 barycoord;
out vec4 fragmentColor;
uniform float is_border;

in vec2 shaderTexCoord;
uniform sampler2D woodTex;
uniform sampler2D goldTex;


void main()
{
    // if ((barycoord.x <= 0.0075f || barycoord.y <= 0.0075f || barycoord.z <= 0.0075f) && is_border == 0.0f) {
    //     fragmentColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    // }
    // else 
    if (shaderColor.x == 1.0f || shaderColor.z == 0.0f) {
        vec4 goldColor = texture(goldTex, shaderTexCoord);
        fragmentColor = goldColor;
    } else {
        vec4 woodColor = texture(woodTex, shaderTexCoord);
        fragmentColor = woodColor;
    }

}
