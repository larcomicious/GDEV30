/******************************************************************************
 * This demo draws a triangle by defining its vertices in 3 dimensions
 * (the 3rd dimension is currently ignored and is just set to 0).
 *
 * The drawing is accomplished by:
 * - Uploading the vertices to the GPU using a Vertex Buffer Object (VBO).
 * - Specifying the vertices' format using a Vertex Array Object (VAO).
 * - Using a GLSL shader program (consisting of a simple vertex shader and a
 *   simple fragment shader) to actually draw the vertices as a triangle.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <gdev.h>
#include <math.h>


// change this to your desired window attributes
#define WINDOW_WIDTH  540
#define WINDOW_HEIGHT 540
#define WINDOW_TITLE  "Hello Triangle"
#define SQUARE_SIZE 800
GLFWwindow *pWindow;

 float vertices2[] = {
     // bottom robe
     -9.031f, -10.0f, 0.0f,0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -6.232f, -7.561f, 0.0f,0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -7.672f, -10.0f, 0.0f,0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
 
     -8.028f, -9.149f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -6.843f, -5.841f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -6.232f, -7.561f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
 
     -6.232f, -7.561f, 0.0f,0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -6.843f, -5.841f, 0.0f,0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -5.411f, -5.523f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
 
     -6.843f, -5.841f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -6.749f, -4.854f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -5.411f, -5.523f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
 
     -6.749f, -4.854f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
     -5.530f, -3.193f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
     -5.411f, -5.523f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
 
     -5.530f, -3.193f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
     -3.130f, -3.059f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
     -3.265f, -3.933f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
 
     -5.411f, -5.523f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
     -5.530f, -3.193f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
     -3.265f, -3.933f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
     
     -5.411f, -5.523f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
     -3.265f, -3.933f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
     -3.495f, -6.010f, 0.0f, 0.20f, 0.18f, 0.11f, -0.04f, 0.01f,
     
     -7.672f, -10.0f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.00f,
     -6.232f, -7.561f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.00f,
     -5.533f, -10.0f, 0.0f, 0.20f, 0.18f, 0.11f,-0.05f, 0.00f,
 
     -5.533f, -10.0f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -6.232f, -7.561f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -4, -8, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
 
     -5.533f, -10.0f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -4, -8, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -4, -10, 0.0f,  0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
 
     -4, -8.8f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -4, -8, 0.0f,0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
     -2.735f, -8.200f, 0.0f, 0.20f, 0.18f, 0.11f, -0.05f, 0.0f,
 
     1.834f, -10.0f, 0.0f,0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     2.224f, -8.933f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     4.384f, -9.051f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
 
     1.834f, -10.0f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     4.384f, -9.051f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     5.5f, -10.0f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
 
     5.5f, -10.0f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     4.384f, -9.051f,  0.0f,0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     8.579f, -9.116f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
 
     5.5f, -10.0f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     8.579f, -9.116f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     8.824f, -10.0f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
 
     4.384f, -9.051f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     8.271f, -7.553f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     8.579f, -9.116f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
 
     6.515f, -8.222f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     5.775f, -6.521f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     8.271f, -7.553f, 0.0f,0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
 
     5.775f, -6.521f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     8.256f, -5.760f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
     8.271f, -7.553f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.0f,
 
     5.775f, -6.521f, 0.0f, 0.20f, 0.18f, 0.11f,  0.05f, 0.01f,
     6.398f, -2.769f, 0.0f, 0.20f, 0.18f, 0.11f,  0.05f, 0.01f,
     8.256f, -5.760f, 0.0f,0.20f, 0.18f, 0.11f,  0.05f, 0.01f,
 
     5.775f, -6.521f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
     4.689f, -3.718f, 0.0f,0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
     6.398f, -2.769f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
 
     4.367f, -5.633f, 0.0f, 0.20f, 0.18f, 0.11f,0.05f, 0.01f,
     4.689f, -3.718f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
     5.775f, -6.521f, 0.0f, 0.20f, 0.18f, 0.11f,0.05f, 0.01f,
 
     3.0f, -6.0f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
     4.689f, -3.718f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
     4.367f, -5.633f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
 
     2.742f, -7.409f, 0.0f, 0.20f, 0.18f, 0.11f,0.05f, 0.01f,
     3.0f, -6.0f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
     4.367f, -5.633f, 0.0f, 0.20f, 0.18f, 0.11f,0.05f, 0.01f,
 
     2.742f, -7.409f, 0.0f, 0.20f, 0.18f, 0.11f,0.05f, 0.01f,
     4.367f, -5.633f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
     4.251f, -7.201f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
     
     4.251f, -7.201f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
     4.367f, -5.633f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
     5.775f, -6.521f, 0.0f, 0.20f, 0.18f, 0.11f, 0.05f, 0.01f,
 
     // inner robe
     -3.495f, -6.010f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -3.265f, -3.933f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -1.853f, -6.375f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
 
     -3.130f, -3.059f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -2.430f, -0.961f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -0.788f, -1.751f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
 
     -3.265f, -3.933f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -3.130f, -3.059f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -0.788f, -1.751f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
 
     -3.265f, -3.933f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -0.788f, -1.751f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -1.573f, -4.120f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     
     -3.265f, -3.933f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -1.573f, -4.120f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -2.282f, -5.827f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
 
     -2.282f, -5.827f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -0.828f, -6.082f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -1.853f, -6.375f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
 
     -2.282f, -5.827f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -0.788f, -1.751f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -0.828f, -6.899f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     
     -1.853f, -6.375f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -0.828f, -6.082f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -0.828f, -6.899f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
 
     -0.788f, -1.751f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     1.401f, -1.599f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
     -0.828f, -6.899f, 0.0f, 0.43f, 0.34f, 0.22f,-0.03f, 0.01f,
 
     // top robe
     1.401f, -1.599f, 0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
     0.7553f, -7.520f, 0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
     -0.828f, -6.899f, 0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
 
     1.401f, -1.599f, 0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
     3.654f, -0.888f,  0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
     0.7553f, -7.520f, 0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
 
     0.7553f, -7.520f, 0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
     3, -6,  0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
     2.742f,  -7.409f, 0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
     
     0.7553f, -7.520f, 0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
     3.654f, -0.888f,  0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
     3, -6,  0.0f, 0.47f, 0.37f, 0.24f, 0.03f, 0.01f,
 
     3, -6,  0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     3.654f, -0.888f,  0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     4.689f, -3.718f, 0.0f,  0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
 
     4.689f, -3.718f, 0.0f,  0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     3.654f, -0.888f,  0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     6.0975f, -0.111f, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
 
     4.689f, -3.718f, 0.0f,  0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     6.0975f, -0.111f, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     6.398f, -2.769f, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
 
     6.398f, -2.769f, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     6.0975f, -0.111f, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     7.223f, -0.795f, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
 
     6.398f, -2.769f, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     7.223f, -0.795f, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     8, -3, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
 
     6.398f, -2.769f, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     8, -3, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
     8.256f, -5.760f, 0.0f, 0.47f, 0.37f, 0.24f, 0.05f, 0.01f,
 
     // sleeves
     -6.232f, -7.561f, 0.0f, 0.34f, 0.25f,0.13f, -0.05f, 0.0f,
     -5.411f, -5.523f, 0.0f, 0.34f, 0.25f,0.13f, -0.05f, 0.0f,
     -3.370f, -6.059f, 0.0f, 0.34f, 0.25f,0.13f, -0.05f, 0.0f,
 
     -6.232f, -7.561f, 0.0f, 0.34f, 0.25f,0.13f, -0.05f, 0.0f,
     -3.370f, -6.059f, 0.0f, 0.34f, 0.25f,0.13f, -0.05f, 0.0f,
     -4, -8,  0.0f,0.34f, 0.25f,0.13f, -0.05f, 0.0f,
 
     -4, -8, 0.0f, 0.34f, 0.25f,0.13f, -0.02f, 0.01f,
     -3.370f, -6.059f, 0.0f, 0.34f, 0.25f,0.13f,-0.02f, 0.01f,
     -1.853f, -6.375f, 0.0f, 0.34f, 0.25f,0.13f, -0.02f, 0.01f,
 
     -4, -8, 0.0f, 0.34f, 0.25f,0.13f,-0.02f, 0.01f,
     -1.853f, -6.375f,  0.0f,0.34f, 0.25f,0.13f,-0.02f, 0.01f,
     -2.735f, -8.200f,  0.0f,0.34f, 0.25f,0.13f,-0.02f, 0.01f,
 
     0.755f, -7.520f, 0.0f, 0.34f, 0.25f,0.13f,0.02f, 0.01f,
     2.742f,  -7.409f, 0.0f, 0.34f, 0.25f,0.13f,0.02f, 0.01f,
     2.224f, -8.933f, 0.0f, 0.34f, 0.25f,0.13f,0.02f, 0.01f,
 
     2.224f, -8.933f, 0.0f, 0.34f, 0.25f,0.13f, 0.05f, 0.0f,
     2.742f,  -7.409f, 0.0f, 0.34f, 0.25f,0.13f, 0.05f, 0.0f,
     4.384f, -9.051f, 0.0f, 0.34f, 0.25f,0.13f, 0.05f, 0.0f,
 
     4.384f, -9.051f, 0.0f, 0.34f, 0.25f,0.13f, 0.05f, 0.0f,
     2.742f,  -7.409f, 0.0f, 0.34f, 0.25f,0.13f, 0.05f, 0.0f,
     4.251f, -7.201f, 0.0f, 0.34f, 0.25f,0.13f, 0.05f, 0.0f,
 
     4.384f, -9.051f, 0.0f, 0.34f, 0.25f,0.13f,0.05f, 0.0f,
     4.251f, -7.201f, 0.0f, 0.34f, 0.25f,0.13f,0.05f, 0.0f,
     6.515f, -8.222f, 0.0f, 0.34f, 0.25f,0.13f,0.05f, 0.0f,
 
     6.515f, -8.222f, 0.0f, 0.34f, 0.25f,0.13f,0.05f, 0.0f,
     4.251f, -7.201f,  0.0f,0.34f, 0.25f,0.13f,0.05f, 0.0f,
     5.775f, -6.521f,  0.0f,0.34f, 0.25f,0.13f,0.05f, 0.0f,
     
     // hair
     -5.530f, -3.193f, 0.0f, 0.15f, 0.09f, 0.09f, -0.04f, 0.01f,
     -4.012f, -0.626f, 0.0f, 0.15f, 0.09f, 0.09f, -0.04f, 0.01f,
     -3.130f, -3.059f, 0.0f, 0.15f, 0.09f, 0.09f, -0.04f, 0.01f,
 
     -4.012f, -0.626f, 0.0f, 0.15f, 0.09f, 0.09f, -0.04f, 0.01f,
     -2.430f, -0.961f, 0.0f, 0.15f, 0.09f, 0.09f, -0.04f, 0.01f,
     -3.130f, -3.059f, 0.0f, 0.15f, 0.09f, 0.09f, -0.04f, 0.01f,
 
     -4.012f, -0.626f, 0.0f, 0.15f, 0.09f, 0.09f, -0.04f, 0.01f,
     -2.795f, 0.620f, 0.0f, 0.15f, 0.09f, 0.09f, -0.04f, 0.01f,
     -2.430f, -0.961f, 0.0f, 0.15f, 0.09f, 0.09f, -0.04f, 0.01f,
 
     -2.430f, -0.961f, 0.0f, 0.15f, 0.09f, 0.09f, -0.02f, 0.01f,
     -2.795f, 0.620f, 0.0f, 0.15f, 0.09f, 0.09f, -0.02f, 0.01f,
     -0.65, -1, 0.0f, 0.15f, 0.09f, 0.09f, -0.02f, 0.01f,
 
     -2, 0,  0.0f,0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -2.795f, 0.620f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -2.491f, 1.745f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
 
     -2.491f, 1.745f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -1.326f, 1.072f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -0.032f, 1.532f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     
     -2.491f, 1.745f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -1.326f, 1.072f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -2, -0.5,  0.0f,0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
 
     -2.491f, 1.745f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -0.032f, 1.532f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -1.326f, 1.072f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
 
     -0.032f, 1.532f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -1.094f, 3.581f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -0.032f,  2.475f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
 
     -2.491f, 1.745f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -1.094f, 3.581f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -0.032f, 1.532f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
 
     -2.491f, 1.745f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -3.069f, 3.722f, 0.0f, 0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
     -1.094f, 3.581f,  0.0f,0.15f, 0.09f, 0.09f,-0.02f, 0.01f,
 
     -3.069f, 3.722f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -1.555f, 5.141f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -1.094f, 3.581f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
 
     -3.069f, 3.722f, 0.0f,0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -2.517f, 6.308f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -1.555f, 5.141f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
 
     -1.555f, 5.141f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -2.517f, 6.308f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -1.396f, 7.159f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
 
     -2.517f, 6.308f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -2.115f, 6.975f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -1.396f, 7.159f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     
     -2.115f, 6.975f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -1.731f, 7.828f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -1.396f, 7.159f,  0.0f,0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
 
     -1.396f, 7.159f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -1.731f, 7.828f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -1.183f, 8.406f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
 
     -1.396f, 7.159f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -1.183f, 8.406f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -0.362f, 8.771f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
 
     -1.396f, 7.159f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -0.362f, 8.771f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
     -0.584f, 7.554f, 0.0f, 0.15f, 0.09f, 0.09f, -0.01f, 0.02f,
 
     -0.584f, 7.554f, 0.0f, 0.15f, 0.09f, 0.09f, 0.0f, 0.01f,
     -0.362f, 8.771f, 0.0f, 0.15f, 0.09f, 0.09f, 0.0f, 0.01f,
     0.376f, 8.976f, 0.0f, 0.15f, 0.09f, 0.09f, 0.0f, 0.01f,
 
     0.376f, 8.976f, 0.0f, 0.15f, 0.09f, 0.09f, 0.01f, 0.02f,
     0.857f, 7.024f, 0.0f, 0.15f, 0.09f, 0.09f, 0.01f, 0.02f,
     -0.094f, 7.574f, 0.0f, 0.15f, 0.09f, 0.09f, 0.01f, 0.02f,
 
     0.376f, 8.976f, 0.0f, 0.15f, 0.09f, 0.09f,0.01f, 0.02f,
     1.377f, 8.820f, 0.0f, 0.15f, 0.09f, 0.09f,0.01f, 0.02f,
     0.857f, 7.024f, 0.0f, 0.15f, 0.09f, 0.09f,0.01f, 0.02f,
 
     0.857f, 7.024f, 0.0f, 0.15f, 0.09f, 0.09f,0.01f, 0.02f,
     1.377f, 8.820f, 0.0f, 0.15f, 0.09f, 0.09f,0.01f, 0.02f,
     1.71f, 6.573f, 0.0f, 0.15f, 0.09f, 0.09f,0.01f, 0.02f,
 
     1.377f, 8.820f, 0.0f, 0.15f, 0.09f, 0.09f,0.01f, 0.02f,
     2.554f, 8.152f, 0.0f, 0.15f, 0.09f, 0.09f,0.01f, 0.02f,
     1.700f, 5.602f, 0.0f, 0.15f, 0.09f, 0.09f,0.01f, 0.02f,
 
     1.700f, 5.602f, 0.0f, 0.15f, 0.09f, 0.09f, 0.01f, 0.01f,
     2.554f, 8.152f,  0.0f,0.15f, 0.09f, 0.09f, 0.01f, 0.01f,
     3.172f, 7.417f, 0.0f, 0.15f, 0.09f, 0.09f, 0.01f, 0.01f,
 
     1.700f, 5.602f, 0.0f, 0.15f, 0.09f, 0.09f, 0.01f, 0.01f,
     3.172f, 7.417f, 0.0f, 0.15f, 0.09f, 0.09f, 0.01f, 0.01f,
     3.731f, 6.073f,  0.0f,0.15f, 0.09f, 0.09f, 0.01f, 0.01f,
 
     1.838f, 4.150f, 0.0f, 0.15f, 0.09f, 0.09f, 0.01f, 0.01f,
     1.700f, 5.602f, 0.0f, 0.15f, 0.09f, 0.09f, 0.01f, 0.01f,
     3.731f, 6.073f, 0.0f, 0.15f, 0.09f, 0.09f, 0.01f, 0.01f,
 
     3.731f, 6.073f, 0.0f, 0.15f, 0.09f, 0.09f, 0.03f, 0.00f,
     3.623f, 4.140f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     1.838f, 4.150f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     1.838f, 4.150f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.623f, 4.140f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.553f, 2.866f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     1.838f, 4.150f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.553f, 2.866f,  0.0f,0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     1.818f,  2.247f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     1.818f,  2.247f, 0.0f, 0.15f, 0.09f, 0.09f,00.03f, 0.00f,
     3.553f, 2.866f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.665f, 1.152f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     1.818f,  2.247f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.665f, 1.152f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     2.149f, 0.500f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     2.149f, 0.500f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.665f, 1.152f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     2.061f, -0.240f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     2.061f, -0.240f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.665f, 1.152f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.654f, -0.888f,  0.0f,0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     2.061f, -0.240f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.654f, -0.888f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     1.401f, -1.599f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     3.654f, -0.888f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     4.754f, 0.956f, 0.0f, 0.15f, 0.09f, 0.09f, 0.03f, 0.00f,
     6.097f, -0.111f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     3.665f, 1.152f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     4.754f, 0.956f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.654f, -0.888f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     3.553f, 2.866f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.731f, 6.073f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     4.754f, 0.956f,  0.0f,0.15f, 0.09f, 0.09f,0.03f, 0.00f,
 
     4.754f, 0.956f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.665f, 1.152f, 0.0f, 0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     3.553f, 2.866f,  0.0f,0.15f, 0.09f, 0.09f,0.03f, 0.00f,
     
     // skin (no shadow)
     // face
     -1.094f, 3.581f, 0.0f, 0.86f, 0.72f, 0.38f,0.0f, 0.02f,
     -0.584f, 7.554f, 0.0f, 0.86f, 0.72f, 0.38f,0.0f, 0.02f,
     1.337f, 3.316f, 0.0f, 0.86f, 0.72f, 0.38f,0.0f, 0.02f,
 
     -0.584f, 7.554f, 0.0f, 0.86f, 0.72f, 0.38f,0.0f, 0.01f,
     0.376f, 8.976f, 0.0f, 0.86f, 0.72f, 0.38f,0.0f, 0.01f,
     -0.094f, 7.574f, 0.0f, 0.86f, 0.72f, 0.38f,0.0f, 0.01f,
 
     -0.584f, 7.554f,  0.0f,0.86f, 0.72f, 0.38f,0.01f, 0.02f,
     -0.094f, 7.574f,  0.0f,0.86f, 0.72f, 0.38f,0.01f, 0.02f,
     1.681f, 6.573f, 0.0f, 0.86f, 0.72f, 0.38f,0.01f, 0.02f,
 
     -0.584f, 7.554f,  0.0f,0.86f, 0.72f, 0.38f,0.025f, 0.01f,
     1.681f, 6.573f, 0.0f, 0.86f, 0.72f, 0.38f,0.025f, 0.01f,
     1.337f, 3.316f,  0.0f,0.86f, 0.72f, 0.38f,0.025f, 0.01f,
 
     -1.094f, 3.581f, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     1.337f, 3.316f,  0.0f,0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     -0.037f, 2.475f, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
 
     -1.094f, 3.581f, 0.0f, 0.86f, 0.72f, 0.38f,-0.01f, 0.02f,
     -1.555f, 5.141f, 0.0f, 0.86f, 0.72f, 0.38f,-0.01f, 0.02f,
     -0.584f, 7.554f, 0.0f, 0.86f, 0.72f, 0.38f,-0.01f, 0.02f,
 
     -1.555f, 5.141f, 0.0f, 0.86f, 0.72f, 0.38f,-0.01f, 0.02f,
     -1.396f, 7.159f,  0.0f,0.86f, 0.72f, 0.38f,-0.01f, 0.02f,
     -0.584f, 7.554f, 0.0f, 0.86f, 0.72f, 0.38f,-0.01f, 0.02f,
    
     // chest
     -2.430f, -0.961f,  0.0f,0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -1.326f, 1.072f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -0.032f, 1.532f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
 
     -2.430f, -0.961f,  0.0f,0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -0.032f, 1.532f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -0.788f, -1.751f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
 
     -0.788f, -1.751f,  0.0f,0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -0.032f, 1.532f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     1.401f, -1.599f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
 
     1.401f, -1.599f, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     -0.032f, 1.532f, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     2.061f, -0.240f, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
 
     2.061f, -0.240f,  0.0f,0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     -0.032f, 1.532f,  0.0f,0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     2.008f, 1.135f,  0.0f,0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     
     2.02f, -0.26f,  0.0f,0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     2.010f, 1.335f,  0.0f,0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     2.3f, 0.500f,  0.0f,0.86f, 0.72f, 0.38f,0.02f, 0.01f,
    
    // hands
     -1.853f, -6.375f,  0.0f,0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -0.828f, -6.899f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -2.735f, -8.200f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
 
     -2.735f, -8.200f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -0.828f, -6.899f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     0.755f, -7.520f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     
     -2.735f, -8.200f, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     0.755f, -7.520f, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     2.224f, -8.933f, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
 
     -2.735f, -8.200f, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     2.224f, -8.933f, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
     2, -10, 0.0f, 0.86f, 0.72f, 0.38f,0.02f, 0.01f,
 
     -4, -10, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -4, -8.808f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -3.246f, -9.445f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
 
     -4, -8.808f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -2.735f, -8.200f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -3.246f, -9.445f,  0.0f,0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
 
     -3.246f, -9.445f,  0.0f,0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -2.735f, -8.200f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -2.770f, -9.428f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
 
     -2.770f, -9.428f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -2.735f, -8.200f, 0.0f, 0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
     -2.277f, -8.634f,  0.0f,0.86f, 0.72f, 0.38f,-0.02f, 0.01f,
 
     // skin (with shadow)
     //neck
     -0.032f, 1.532f, 0.0f, 0.79f, 0.61f, 0.26f,0.025f, 0.01f,
     -0.037f, 2.475f, 0.0f, 0.79f, 0.61f, 0.26f,0.025f, 0.01f,
     2.008f, 1.135f, 0.0f, 0.79f, 0.61f, 0.26f,0.025f, 0.01f,
 
     2.008f, 1.135f, 0.0f, 0.79f, 0.61f, 0.26f,0.025f, 0.01f,
     -0.037f, 2.475f, 0.0f, 0.79f, 0.61f, 0.26f,0.025f, 0.01f,
     1.337f, 3.316f, 0.0f, 0.79f, 0.61f, 0.26f,0.025f, 0.01f,
 
     1.337f, 3.316f, 0.0f, 0.79f, 0.61f, 0.26f,0.025f, 0.01f,
     1.681f, 6.573f, 0.0f, 0.79f, 0.61f, 0.26f,0.025f, 0.01f,
     2.008f, 1.135f, 0.0f, 0.79f, 0.61f, 0.26f,0.025f, 0.01f,
 
     // hands
     -4, -10,  0.0f,0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
     -3.246f, -9.4f, 0.0f,0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
     -1.50f, -10,  0.0f,0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
 
     -1.50f, -10, 0.0f, 0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
     -3.246f, -9.4f, 0.0f, 0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
     -1.159f, -9.4f,  0.0f,0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
 
     1.5f, -10, 0.0f, 0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
     2.072f, -9.652f, 0.0f, 0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
     2, -10,  0.0f,0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
 
     -2.735f, -8.200f, 0.0f, 0.79f, 0.61f, 0.26f,0.02f, 0.01f,
     2, -10,  0.0f,0.79f, 0.61f, 0.26f,0.02f, 0.01f,
     -1.5f, -9.4f,  0.0f,0.79f, 0.61f, 0.26f,0.02f, 0.01f,
 
     -1.5f, -9.4f,  0.0f,0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
     -2.77f, -9.4f, 0.0f,0.79f, 0.61f, 0.26f,-0.02f, 0.01f,
     -2.277f, -8.634f,  0.0f,0.79f, 0.61f, 0.26f,-0.02f, 0.01f,

     -1.50f, -10, 0.0f, 0.20f, 0.18f, 0.11f,0.02f, 0.01f,
    -1.159f, -9.4f,  0.0f,0.20f, 0.18f, 0.11f,0.02f, 0.01f,
    2.0f, -10.0f,  0.0f, 0.20f, 0.18f, 0.11f,0.02f, 0.01f,
 };

float painting_colors[] = {
    0.20f, 0.18f, 0.11f,
    0.43f, 0.34f, 0.22f,
    0.47f, 0.37f, 0.24f,
    0.34f, 0.25f,0.13f,
    0.15f, 0.09f, 0.09f,
    0.86f, 0.72f, 0.38f,
    0.79f, 0.61f, 0.26f,
};

// define a vertex array to hold our vertices
std::vector<float> vertices;

float colors[] =  {
    156, 137, 192,
    175, 147, 195,
    189, 155, 192,
    202, 158, 185,
    233, 163, 171,
    234, 165, 149,
    247, 165, 117,
    253, 159, 59,
    252, 143, 14,
    253, 120, 1,
    237, 75, 0
};

std::vector<int> y_interval;

std::vector<float> vertices1 =
    {
        -10.0f, 10.0f,
        -10.0f, 8.0f,
        10.0f, 8.0f,

        10.0f, 10.0f,
        -10.0f, 10.0f,
        10.0f, 8.0f,
    };

// define OpenGL object IDs to represent the vertex array and the shader program in the GPU
GLuint vao;         // vertex array object (stores the render state for our vertex array)
GLuint vbo;         // vertex buffer object (reserves GPU memory for our vertex array)
GLuint shader;      // combined vertex and fragment shader
constexpr float POINT_MAX = 50.0f;
GLuint bg_texture;
GLuint swirl_texture;
GLuint mona_lisa;
// called by the main function to do initial setup, such as uploading vertex
// arrays, shader programs, etc.; returns true if successful, false otherwise
bool setup()
{
    GLfloat borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    bg_texture = gdevLoadTexture("mona_bg.jpg", GL_CLAMP_TO_BORDER, true, true);
    swirl_texture = gdevLoadTexture("swirl_texture.jpg", GL_REPEAT, true, true);
    mona_lisa = gdevLoadTexture("mona.png", GL_REPEAT, true, true);
    if (!bg_texture) return false;
    if (!swirl_texture) return false;
    if (!mona_lisa) return false;


    // generate the VAO and VBO objects and store their IDs in vao and vbo, respectively
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // bind the newly-created VAO to make it the current one that OpenGL will apply state changes to
    glBindVertexArray(vao);

    // upload our vertex array data to the newly-created VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // on the VAO, register the current VBO with the following vertex attribute layout:
    // - layout location 0...
    // - ... shall consist of 3 GL_FLOATs (corresponding to x, y, and z coordinates)
    // - ... its values will NOT be normalized (GL_FALSE)
    // - ... the stride length is the number of bytes of all 3 floats of each vertex (hence, 3 * sizeof(float))
    // - ... and we start at the beginning of the array (hence, (void*) 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*) (6 * sizeof(float)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*) (8 * sizeof(float)));
    // enable the newly-created layout location 0;
    // this shall be used by our vertex shader to read the vertex's x, y, and z
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    // important: if you have more vertex arrays to draw, make sure you separately define them
    // with unique VAO and VBO IDs, and follow the same process above to upload them to the GPU

    // load our shader program
    shader = gdevLoadShader("Exercise2.vs", "Exercise2.fs");
    if (! shader)
        return false;

    return true;
}

// called by the main function to do rendering per frame
void render()
{
    // clear the whole frame
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // using our shader program...
    glUseProgram(shader);

    float t = glfwGetTime();
    glUniform1f(glGetUniformLocation(shader, "t"), t);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bg_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, swirl_texture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mona_lisa);

    glUniform1i(glGetUniformLocation(shader,"bg_texture"), 0);
    glUniform1i(glGetUniformLocation(shader,"swirl_texture"), 1);
    glUniform1i(glGetUniformLocation(shader,"mona_lisa"), 2);

    // ... draw our triangles
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, (vertices.size() * sizeof(vertices)) / (10 * sizeof(float)));
}

/*****************************************************************************/

// handler called by GLFW when there is a keyboard event
void handleKeys(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    // pressing Esc closes the window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
}

// handler called by GLFW when the window is resized
void handleResize(GLFWwindow* pWindow, int width, int height)
{
    // tell OpenGL to do its drawing within the entire "client area" (area within the borders) of the window
    glViewport(0, 0, width, height);
}

std::vector<float> gradientRGB(float cur_y) {
    for (int i = 0; i < 10; i++) {
        float start_y = y_interval[i];
        float end_y = y_interval[i+1];

        float r_start = colors[i*3];
        float r_end  = colors[(i+1)*3];
        float g_start = colors[i*3+1];
        float g_end  = colors[(i+1)*3+1];
        float b_start = colors[i*3+2];
        float b_end  = colors[(i+1)*3+2];

        float r_delta = r_end - r_start;
        float g_delta = g_end - g_start;
        float b_delta = b_end - b_start;

        if (start_y <= cur_y && cur_y <= end_y) {
            float lerp_factor_1 = (cur_y-start_y)/(end_y-start_y);

            std::vector<float> new_color = {
              r_start + r_delta*lerp_factor_1, g_start + g_delta*lerp_factor_1, b_start + b_delta*lerp_factor_1
            };

            return {new_color[0]/255.0f, new_color[1]/255.0f, new_color[2]/255.0f};
        }
    }
    return {};
}

// main function
int main(int argc, char** argv)
{

    for (int i = 0; i <= 10; i++) {
        y_interval.push_back(-10.0f + (float)i * 2.0f);
    }

    for (int i = 0; i < 9; i++) {
        vertices1.push_back(vertices1[vertices1.size()-12]);
        vertices1.push_back(vertices1[vertices1.size()-12]-2.0f);
        vertices1.push_back(vertices1[vertices1.size()-12]);
        vertices1.push_back(vertices1[vertices1.size()-12]-2.0f);
        vertices1.push_back(vertices1[vertices1.size()-12]);
        vertices1.push_back(vertices1[vertices1.size()-12]-2.0f);
        vertices1.push_back(vertices1[vertices1.size()-12]);
        vertices1.push_back(vertices1[vertices1.size()-12]-2.0f);
        vertices1.push_back(vertices1[vertices1.size()-12]);
        vertices1.push_back(vertices1[vertices1.size()-12]-2.0f);
        vertices1.push_back(vertices1[vertices1.size()-12]);
        vertices1.push_back(vertices1[vertices1.size()-12]-2.0f);
    }


    for (int i = 0; i < 3*2*10; i++) {
        int cur = i*2;
        float x = vertices1[cur];
        float y = vertices1[cur+1];
        std::vector<float> color = gradientRGB(y);
        std::vector<float> cur_point = {x, y, 0.0f, color[0], color[1], color[2], 0.0f, 0.0f, (x+10.0f)/20.0f, (y+10.0f)/20.0f};
        vertices.insert(vertices.end(), cur_point.begin(), cur_point.end());
    }

    for (float i = 0; i < sizeof(vertices2)/(sizeof(float) * 8); i++) {
        int start = i*8;

        std::vector<float> new_color = gradientRGB(vertices2[start+1]);

        // This is where the preset "mona lisa" vertices are being added
        std::vector<float> current_vertex = {vertices2[start], vertices2[start+1], vertices2[start+2], new_color[0], new_color[1], new_color[2], vertices2[start+6], vertices2[start+7], (vertices2[start]+11.0f)/22.0f, (vertices2[start+1]+11.0f)/22.0f};
        vertices.insert(vertices.end(), current_vertex.begin(), current_vertex.end());
    }
    


    // initialize GLFW and ask for OpenGL 3.3 core
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // create a GLFW window with the specified width, height, and title
    pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (! pWindow)
    {
        // gracefully terminate if we cannot create the window
        std::cout << "Cannot create the GLFW window.\n";
        glfwTerminate();
        return -1;
    }

    std::vector<glm::vec2> test_points;
    for (int i = 0; i < 81; i++) {
        int cur = i*2;
        test_points.push_back(glm::vec2(vertices1[cur], vertices1[cur+1]));
    }

    // make the window the current context of subsequent OpenGL commands,
    // and enable vertical sync and aspect-ratio correction on the GLFW window
    glfwMakeContextCurrent(pWindow);
    glfwSwapInterval(1);
    glfwSetWindowAspectRatio(pWindow, WINDOW_WIDTH, WINDOW_HEIGHT);

    // set up callback functions to handle window system events
    glfwSetKeyCallback(pWindow, handleKeys);
    glfwSetFramebufferSizeCallback(pWindow, handleResize);

    // don't miss any momentary keypresses
    glfwSetInputMode(pWindow, GLFW_STICKY_KEYS, GLFW_TRUE);

    // initialize GLAD, which acts as a library loader for the current OS's native OpenGL library
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // if our initial setup is successful...
    if (setup())
    {
        // do rendering in a loop until the user closes the window
        while (! glfwWindowShouldClose(pWindow))
        {
            // render our next frame
            // (by default, GLFW uses double-buffering with a front and back buffer;
            // all drawing goes to the back buffer, so the frame does not get shown yet)
            render();

            // swap the GLFW front and back buffers to show the next frame
            glfwSwapBuffers(pWindow);

            // process any window events (such as moving, resizing, keyboard presses, etc.)
            glfwPollEvents();
        }
    }

    // gracefully terminate the program
    glfwTerminate();
    return 0;
}
