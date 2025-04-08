/******************************************************************************
 * This is a really simple vertex shader that simply sets the output vertex's
 * position to be the same as the input.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 norm;

uniform mat4 matrix;
uniform mat4 model;
uniform vec3 lightPos;
out vec3 shaderColor;
out vec3 barycoord;
out vec3 normal;
out vec3 fragPos;
out vec3 trans;
out mat3 rotate;
out vec3 final_light_pos;
out vec2 shaderTexCoord;

void main()
{
    gl_Position = matrix * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0f);
    
    // mat3 normalMatrix = mat3(matrix);
    // normalMatrix = inverse(normalMatrix);
    // normalMatrix = transpose(normalMatrix);

    shaderColor = vertexColor;
    fragPos = vec3(model * vec4(vertexPosition, 1.0f));
    final_light_pos = vec3(model * vec4(lightPos, 1.0f));

    if ((gl_VertexID%3) == 0) {
        barycoord = vec3(1.0f, 0.0f, 0.0f);
    } else if ((gl_VertexID%3) == 1) {
        barycoord = vec3(0.0f, 1.0f, 0.0f);
    } else {
        barycoord = vec3(0.0f, 0.0f, 1.0f);
    }
    
    rotate[0] = model[0].xyz;
    rotate[1] = model[1].xyz;
    rotate[2] = model[2].xyz;
    trans = vec3(model[0][3], model[1][3], model[2][3]);
    normal = normalize(rotate * norm);

    vec3 absNormal = abs(norm);
    if (absNormal.z > absNormal.x && absNormal.z > absNormal.y) {
        shaderTexCoord = vertexPosition.xy;
    } else if (absNormal.x > absNormal.y) {
        shaderTexCoord = vertexPosition.yz;
    } else {
        shaderTexCoord = vertexPosition.xz;
    }
}

