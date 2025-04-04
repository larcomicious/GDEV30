/******************************************************************************
 * This is a really simple fragment shader that simply sets the output fragment
 * color to yellow.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

in vec3 shaderColor;
in vec2 textureCoord;
in vec2 animID;
out vec4 fragmentColor;
uniform float t;
uniform sampler2D bg_texture;
uniform sampler2D swirl_texture;
uniform sampler2D mona_lisa;

void main()
{
    vec4 bg_color = texture(bg_texture, textureCoord);
    vec4 shaderColRGBA = vec4(shaderColor, 1.0f);

    float new_t = clamp(abs(2 * sin(2 * 3.141592 *(-0.1 * t + 0.5)))-0.5, 0, 1);

    vec4 swirl_color = texture(swirl_texture, textureCoord);
    float grey = swirl_color.r*2 - 1.0f;
    vec2 disp = 0.2f * vec2(1, 1) * grey * new_t;

    if (animID.x == 0.0f && animID.y == 0.0f){
        vec4 bg_color = texture(bg_texture, textureCoord);
        fragmentColor = mix(shaderColRGBA, bg_color, 0.7f);
    } else {
        vec4 mona_lisa_color = texture(mona_lisa, textureCoord+disp);
        fragmentColor = mix(shaderColRGBA, mona_lisa_color, 0.7f);
    }
}
