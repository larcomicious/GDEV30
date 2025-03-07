/******************************************************************************
 * This is a really simple fragment shader that simply sets the output fragment
 * color to yellow.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

in vec3 shaderColor;
in vec2 shaderTexCoord;
uniform sampler2D shaderTexture;
uniform float t;
uniform float theta;
out vec4 fragmentColor;
uniform sampler2D shaderTextureA;
uniform sampler2D shaderTextureB;

mat2 rotate(float angle)
{
    return mat2(
        cos(angle), -sin(angle),
        sin(angle), cos(angle)
    );
}

void main()
{
    fragmentColor = vec4(shaderColor, 1.0f) * texture(shaderTexture, shaderTexCoord* vec2(-1.0f, 1.0f));
    vec4 colorA = texture(shaderTextureA, shaderTexCoord);
    vec4 colorB = texture(shaderTextureB, shaderTexCoord+vec2(0.2f*t,0.2f*t));
    fragmentColor = mix(colorA, colorB, (sin(t)+1)/2);
}
