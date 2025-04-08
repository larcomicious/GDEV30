/******************************************************************************
 * This is a really simple fragment shader that simply sets the output fragment
 * color to yellow.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

in vec3 shaderColor;
in vec3 barycoord;
in vec3 normal;
in vec3 fragPos;
in vec3 trans;
in mat3 rotate;
in vec3 final_light_pos;
out vec4 fragmentColor;
uniform float is_border;

in vec2 shaderTexCoord;
uniform sampler2D woodTex;
uniform sampler2D goldTex;


void main()
{
    float grayscale;
    float gray_strength = 0.7;

    // texturing
    if (shaderColor.x == 1.0f || shaderColor.z == 0.0f) {
        vec4 gold = texture(goldTex, shaderTexCoord);
        grayscale = mix(1.0f, gold.r, gray_strength);
    } else {
        vec4 wood = texture(woodTex, shaderTexCoord);
        grayscale = mix(1.0f, wood.r, gray_strength);
    }

    // lighting
    float ambientStrength = 0.75f;
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDir = normalize(final_light_pos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0f);
    float light_dist = distance(final_light_pos, fragPos);

    if (light_dist >= 0.15f) {
        diff = 0.0f;
        //light_dist = 0.0f;
    }
    
    vec3 diffuse = diff * lightColor;
    
    fragmentColor = vec4((ambient + diffuse) * shaderColor * grayscale, 1.0f);

    // outlines
    // if ((barycoord.x <= 0.0075f || barycoord.y <= 0.0075f || barycoord.z <= 0.0075f) && is_border == 0.0f) {
    //     fragmentColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    // }

}
