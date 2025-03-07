/******************************************************************************
 * This demo draws a somewhat familiar geometric object composed of three
 * triangles.
 *
 * The main differences between this demo and the previous demo are:
 * - Each   now defines two subcomponents: position and color.
 * - A uniform variable is introduced to the shader program, which is used to
 *   accomplish a glowing effect.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>
#include <cmath>
#include <numeric>
#include <vector>


// change this to your desired window attributes
#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 576

#define WINDOW_TITLE  "Hello Trifxxxe"
#define PI           3.14159265358979323846
typedef std::pair<float, float> pff;
GLFWwindow *pWindow;
const int circle_sides = 90;
const float bg_r = 0.255f;
const float bg_g = 0.412f;
const float bg_b = 0.882f;

// define OpenGL object IDs to represent the vertex array and the shader program in the GPU
GLuint vao;         // vertex array object (stores the render state for our vertex array)
GLuint vbo;         // vertex buffer object (reserves GPU memory for our vertex array)
GLuint shader;      // combined vertex and fragment shader
std::vector<float> vertices;

// Circle in cartesian geometry based on window height
struct Circle {
    float center_x, center_y;
    float radius;
    float r, g, b;
    float rotSpeed;

    Circle(float x, float y, float rad, float r, float g, float b, float rotSpeed) {
        this->center_x = x;
        this->center_y = y;
        this->radius = rad;
        this->r = r;
        this->g = g;
        this->b = b;
        this->rotSpeed = rotSpeed;
    }

    std::vector<float> circleVertices() {
        std::vector<float> current_vertices;
        float firstX = center_x;
        float firstY = center_y + radius;
    
        float angle = 360.0f / circle_sides;
    
        std::vector<pff> test = {{firstX, firstY}}; 
    
        for (int i = 1; i < circle_sides; i++) {
            float prevX = test[i-1].first-center_x;
            float prevY = test[i-1].second-center_y;
            
            float rad = angle*PI/180.0f;
            float newX = prevX * cos(rad) - prevY * sin(rad);
            float newY = prevX * sin(rad) + prevY * cos(rad);
    
            test.push_back({newX+center_x, newY+center_y});    
        }
    
        
        // float half_width = (float)WINDOW_WIDTH/2.0f;
        // float half_height = (float)WINDOW_HEIGHT/2.0f;

        // int width_ratio = WINDOW_WIDTH / std::gcd(WINDOW_WIDTH, WINDOW_HEIGHT);
        // int height_ratio = WINDOW_HEIGHT / std::gcd(WINDOW_WIDTH, WINDOW_HEIGHT);
        // float smaller = std::min(width_ratio, height_ratio);

        // std::cout << "why: " << half_width << " " << half_height << std::endl;


        for (int i = 0; i < circle_sides; i++) {
            pff p1 = test[(((i-1)%circle_sides)+circle_sides)%circle_sides];
            pff p2 = test[(((i)%circle_sides)+circle_sides)%circle_sides];
    
    
            std::vector<float> vert1 = {(p1.first ) , (p1.second), 0.0f, r, g, b, rotSpeed, 0.0f, 0.0f};
            current_vertices.insert(current_vertices.end(), vert1.begin(), vert1.end());
        
            std::vector<float> vert2 = {(center_x ), (center_y ) , 0.0f, r, g, b, rotSpeed, 0.0f, 0.0f};
            current_vertices.insert(current_vertices.end(), vert2.begin(), vert2.end());

            std::vector<float> vert3 = {(p2.first ), (p2.second ), 0.0f, r, g, b, rotSpeed, 0.0f, 0.0f};
            current_vertices.insert(current_vertices.end(), vert3.begin(), vert3.end());
        }
        //std::cout << std::endl;
        return current_vertices;
    }
};

struct Triangle {
    float x_1, y_1, x_2, y_2, x_3, y_3;
    float r, g, b;
    float rotSpeed;

    Triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3, float r, float g, float b, float rotSpeed) {
        this->x_1 = x_1;
        this->y_1 = y_1;
        this->x_2 = x_2;
        this->y_2 = y_2;
        this->x_3 = x_3;
        this->y_3 = y_3;
        this->r = r;
        this->g = g;
        this->b = b;
        this->rotSpeed = rotSpeed;
    }

    std::vector<float> triangleVertices() {
        std::vector<float> current_vertices = {
            x_1, y_1, 0.0f, r, g, b, rotSpeed, 0.0f, 0.0f,
            x_2, y_2, 0.0f, r, g, b, rotSpeed, 0.0f, 0.0f,
            x_3, y_3, 0.0f, r, g, b, rotSpeed, 0.0f, 0.0f
        };
        
        return current_vertices;
    }
};

struct Rectangle {
    float bottom_left_x, bottom_left_y;
    float width, height; 
    float r, g, b;
    float rotSpeed, clock_no;

    Rectangle(float x, float y, float wid, float hei, float r, float g, float b, float rotSpeed, float clock_no) {
        this->bottom_left_x = x;
        this->bottom_left_y = y;
        this->width = wid;
        this->height = hei;
        this->r = r;
        this->g = g;
        this->b = b;
        this->rotSpeed = -rotSpeed;
        this->clock_no = clock_no;
    }

    std::vector<float> rectangleVertices(){
        std::vector<float> current_vertices;
        
        // float half_width = (float)WINDOW_WIDTH/2.0f;
        // float half_height = (float)WINDOW_HEIGHT/2.0f;


        std::vector<float> bottom_left = {bottom_left_x, bottom_left_y, 0.0f, r, g, b,rotSpeed, clock_no, 0.0f};
        std::vector<float> bottom_right = {bottom_left_x+width, bottom_left_y, 0.0f, r, g, b, rotSpeed, clock_no, 0.0f};
        std::vector<float> top_left = {bottom_left_x, bottom_left_y+height, 0.0f, r, g, b, rotSpeed, clock_no, 0.0f};
        std::vector<float> top_right = {bottom_left_x+width, bottom_left_y+height, 0.0f, r, g, b, rotSpeed, clock_no, 0.0f};

        current_vertices.insert(current_vertices.end(), bottom_left.begin(), bottom_left.end());
        current_vertices.insert(current_vertices.end(), top_right.begin(), top_right.end());
        current_vertices.insert(current_vertices.end(), top_left.begin(), top_left.end());

        current_vertices.insert(current_vertices.end(), bottom_left.begin(), bottom_left.end());
        current_vertices.insert(current_vertices.end(), top_right.begin(), top_right.end());
        current_vertices.insert(current_vertices.end(), bottom_right.begin(), bottom_right.end());

        return current_vertices;
    }

    std::vector<float> rotatedVertices(float x, float y, float theta){
        std::vector<float> current_vertices;
        float left_x = bottom_left_x;
        float right_x = bottom_left_x + width;
        float down_y = bottom_left_y;
        float up_y = bottom_left_y + height;

        float left_x_trans = left_x - x;
        float right_x_trans = right_x - x;
        float down_y_trans = down_y - y;
        float up_y_trans = up_y - y;

        float rad = theta*PI/180.0f;

        std::vector<float> bottom_left = {cos(rad)*left_x_trans - sin(rad)*down_y_trans, sin(rad)*left_x_trans + cos(rad)*down_y_trans, 0.0f, r, g, b, rotSpeed, 0.0f, 0.0f};
        std::vector<float> bottom_right = {cos(rad)*right_x_trans - sin(rad)*down_y_trans, sin(rad)*right_x_trans + cos(rad)*down_y_trans, 0.0f, r, g, b, rotSpeed, 0.0f, 0.0f};
        std::vector<float> top_left = {cos(rad)*left_x_trans - sin(rad)*up_y_trans, sin(rad)*left_x_trans + cos(rad)*up_y_trans, 0.0f, r, g, b, rotSpeed, 0.0f, 0.0f};
        std::vector<float> top_right = {cos(rad)*right_x_trans - sin(rad)*up_y_trans, sin(rad)*right_x_trans + cos(rad)*up_y_trans, 0.0f, r, g, b, rotSpeed, 0.0f, 0.0f};

        current_vertices.insert(current_vertices.end(), bottom_left.begin(), bottom_left.end());
        current_vertices.insert(current_vertices.end(), top_right.begin(), top_right.end());
        current_vertices.insert(current_vertices.end(), top_left.begin(), top_left.end());
        current_vertices.insert(current_vertices.end(), bottom_left.begin(), bottom_left.end());
        current_vertices.insert(current_vertices.end(), top_right.begin(), top_right.end());
        current_vertices.insert(current_vertices.end(), bottom_right.begin(), bottom_right.end());

        return current_vertices;
    }
};

struct Star {
    float center_x, center_y;
    float radius;
    float r, g, b;
    float rotSpeed;
    float anim_cycle;

    Star(float x, float y, float rad, float r, float g, float b, float rotSpeed, float anim_cycle) {
        this->center_x = x;
        this->center_y = y;
        this->radius = rad;
        this->r = r;
        this->g = g;
        this->b = b;
        this->rotSpeed = rotSpeed;
        this->anim_cycle = anim_cycle;
    }

    std::vector<float> starVertices(){
        std::vector<float> current_vertices;
        std::vector<pff> middlePoints = {{center_x - radius, center_y}, {center_x, center_y + radius}, {center_x + radius, center_y}, {center_x, center_y - radius}};
        std::vector<pff> cornerPoints = {{center_x - radius, center_y + radius}, {center_x + radius, center_y + radius}, {center_x + radius, center_y - radius}, {center_x - radius, center_y - radius}};
        std::vector<pff> currentPoints = {middlePoints[0]};

        for (int i = 0; i < 4; i++) {
            // pff startingPoint = middlePoints[i];
            pff rotationPoint = cornerPoints[i];
            float angle = 360.0f / circle_sides;
            float rad = angle*PI/180.0f;
            for (int j = 0; j < circle_sides/4; j++) {
                pff prevPoint = currentPoints[currentPoints.size()-1];
                pff translated = {prevPoint.first-rotationPoint.first, prevPoint.second-rotationPoint.second};

                pff rotatedPoint = {(cos(rad)*translated.first - sin(rad)*translated.second) + rotationPoint.first, (sin(rad)*translated.first + cos(rad)*translated.second) + rotationPoint.second};
                currentPoints.push_back(rotatedPoint);
            }
        }

        for (int i = 0; i < currentPoints.size(); i++) {
            pff p1 = currentPoints[(((i)%currentPoints.size())+currentPoints.size())%currentPoints.size()];
            pff p2 = currentPoints[(((i+1)%currentPoints.size())+currentPoints.size())%currentPoints.size()];
    
    
            std::vector<float> vert1 = {(p1.first ) , (p1.second), 0.0f, r, g, b, rotSpeed, 1.0f, anim_cycle};
            current_vertices.insert(current_vertices.end(), vert1.begin(), vert1.end());
        
            std::vector<float> vert2 = {(center_x ), (center_y ) , 0.0f, r, g, b, rotSpeed, 1.0f, anim_cycle};
            current_vertices.insert(current_vertices.end(), vert2.begin(), vert2.end());

            std::vector<float> vert3 = {(p2.first ), (p2.second ), 0.0f, r, g, b, rotSpeed, 1.0f, anim_cycle};
            current_vertices.insert(current_vertices.end(), vert3.begin(), vert3.end());
        }

        return current_vertices;
    }
};

// called by the main function to do initial setup, such as uploading vertex
// arrays, shader programs, etc.; returns true if successful, false otherwise
bool setup()
{
    // generate the VAO and VBO objects and store their IDs in vao and vbo, respectively
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // bind the newly-created VAO to make it the current one that OpenGL will apply state changes to
    glBindVertexArray(vao);


    // Setting alpha to mean something
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // upload our vertex array data to the newly-created VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // on the VAO, register the current VBO with the following vertex attribute layout:
    // - the stride length of the vertex array is 6 floats (6 * sizeof(float))
    // - layout location 0 (position) is 3 floats and starts at the first float of the vertex array (offset 0)
    // - layout location 1 (color) is also 3 floats but starts at the fourth float (offset 3 * sizeof(float))
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (6 * sizeof(float)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (7 * sizeof(float)));

    // enable the layout locations so they can be used by the vertex shader
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    // important: if you have more vertex arrays to draw, make sure you separately define them
    // with unique VAO and VBO IDs, and follow the same process above to upload them to the GPU

    // load our shader program
    shader = gdevLoadShader("exercise_1.vs", "exercise_1.fs");
   


    if (! shader) {
        return false;
    }


    return true;
}


// define a vertex array to hold our vertices
// float vertices[] =
// {
//     // position (x, y, z)    color (r, g, b)
//     -0.40f, -0.50f,  0.00f,  1.0f, 1.0f, 1.0f,
//      0.00f, -0.50f,  0.00f,  1.0f, 1.0f, 0.0f,
//     -0.20f,  0.00f,  0.00f,  1.0f, 1.0f, 0.0f,
//      0.00f, -0.50f,  0.00f,  1.0f, 1.0f, 0.0f,
//      0.40f, -0.50f,  0.00f,  1.0f, 1.0f, 1.0f,
//      0.20f,  0.00f,  0.00f,  1.0f, 1.0f, 0.0f,
//     -0.20f,  0.00f,  0.00f,  1.0f, 1.0f, 0.0f,
//      0.20f,  0.00f,  0.00f,  1.0f, 1.0f, 0.0f,
//      0.00f,  0.50f,  0.00f,  1.0f, 1.0f, 1.0f
// };

// define a vertex array to hold our vertices


// called by the main function to do rendering per frame
void render()
{
    // clear the whole frame
    glClearColor(bg_r, bg_g, bg_b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // compute a value for the glow amount for this frame
    float glow = fabs(sin(glfwGetTime() / 3.0f)) / 2.0f + 0.5f;
    float t = glfwGetTime();

    int time_int = (int)t;
    float percent = t-time_int;
    // using our shader program...
    glUseProgram(shader);

    // ... set the uniform variables of the shader...
    // (in this case, simply set the value of the glow)
    glUniform1f(glGetUniformLocation(shader, "glow"), glow);
    glUniform1f(glGetUniformLocation(shader, "t"), t);
    glUniform1f(glGetUniformLocation(shader, "percent"), percent);
    glUniform1i(glGetUniformLocation(shader, "shift"), time_int);
    glUniform2f(glGetUniformLocation(shader, "windowDimensions"), (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);

    // ... then draw our triangles
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, (vertices.size() * sizeof(float)) / (9 * sizeof(float)));
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

void addToVertices(Rectangle* x) {
    std::vector<float> rect_verts = x->rectangleVertices();
    vertices.insert(vertices.end(), rect_verts.begin(), rect_verts.end());
}

void addToVertices(Circle* x) {
    std::vector<float> circle_verts = x->circleVertices();
    vertices.insert(vertices.end(), circle_verts.begin(), circle_verts.end());
}

void addToVertices(Triangle* x) {
    std::vector<float> triangle_verts = x->triangleVertices();
    vertices.insert(vertices.end(), triangle_verts.begin(), triangle_verts.end());
}

void addToVertices(Star* x) {
    std::vector<float> star_verts = x->starVertices();
    vertices.insert(vertices.end(), star_verts.begin(), star_verts.end());
}


// main function
int main(int argc, char** argv)
{

    // Main Clock
    // Minute Hand
    Rectangle r1(0.0f, 2.5f, 190.0f, 5.0f, 1.0f, 1.0f, 1.0f, 12.0f / 720.0f, 0);
    Rectangle r2(0.0f, -2.5f, 200.0f, 5.0f, 1.0f, 1.0f, 1.0f, 12.0f / 720.0f, 0);
    Rectangle r3(0.0f, -7.5f, 170.0f, 5.0f, 1.0f, 1.0f, 1.0f, 12.0f / 720.0f, 0);

    // Hour Hand
    Rectangle r4(-2.5f, 0.0f, 5.0f, 200.0f, 1.0f, 1.0f, 1.0f, 1.0f / 720.0f, 0);
    Rectangle r5(-7.5f, 0.0f, 5.0f, 190.0f, 1.0f, 1.0f, 1.0f, 1.0f / 720.0f, 0);
    Rectangle r6(2.5f, 0.0f, 5.0f, 180.0f, 1.0f, 1.0f, 1.0f, 1.0f / 720.0f, 0);
    Rectangle r7(-12.5f, 0.0f, 5.0f, 170.0f, 1.0f, 1.0f, 1.0f, 1.0f / 720.0f, 0);
    Rectangle r8(7.5f, 0.0f, 5.0f, 160.0f, 1.0f, 1.0f, 1.0f, 1.0f / 720.0f, 0);

    // Second Hand
    Rectangle r9(-200.0f, -2.5f, 200.0f, 5.0f, 0.7f, 0.7f, 0.0f, 720.0f / 720.0f, 0);

    // Circles 
    Circle big_white(0.0f, 0.0f, 150.0f, 1.0f, 1.0f, 1.0f, 0.0f);
    Circle bg_circle(0.0f, 0.0f, 145.0f, bg_r, bg_g, bg_b, 0.0f);
    Circle small_white(0.0f, 0.0f, 50.0f, 1.0f, 1.0f, 1.0f, 0.0f);

    // Butler Clock 1
    float clock_width = 75.0f;
    float clock_x = -360.0f;
    float clock_y = -150.0f;
    // Body
    Circle clock_circle1(clock_x, clock_y, clock_width, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_hand1(clock_x+clock_width*1.05f, clock_y-clock_width/5, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_hand2(clock_x-clock_width*1.05f, clock_y-clock_width/5, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_foot1(clock_x+clock_width*0.4f, clock_y-clock_width*0.9f, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_foot2(clock_x-clock_width*0.4f, clock_y-clock_width*0.9f, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_horn1(clock_x+clock_width, clock_y-clock_width*0.9f, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_horn2(clock_x+clock_width, clock_y-clock_width*0.9f, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_circle2(clock_x, clock_y, clock_width*0.85, 1.0f, 1.0f, 1.0f, 0.0f);
        
    // Clock Hands
    // Minute Hand
    Rectangle h1(clock_x-2.5f, clock_y, 5.0f, clock_width*0.6f, 0.215f, 0.215f, 0.215f, 12.0f / 720.0f, 2);
    // Hour Hand
    Rectangle h2(clock_x-2.0f, clock_y, 4.0f, clock_width*0.8f, 0.215f, 0.215f, 0.215f, 1.0f / 720.0f, 2);
    // Second Hand
    Rectangle h3(clock_x-1.0f, clock_y, 2.0f, clock_width*0.7f, 1.0f, 0.2f, 0.2f, 720.0f / 720.0f, 2);
    // Center Circle 1
    Circle clock_circle3(clock_x, clock_y, clock_width*0.1f, 0.215f, 0.215f, 0.215f, 0.0f);
    Circle clock_circle4(clock_x, clock_y, clock_width*0.05f, 1.0f, 1.0f, 1.0, 0.0f);
    
    // Hat
    Rectangle hat1(clock_x-clock_width*0.4f, clock_y+clock_width*1.02f, clock_width*0.8f, clock_width*0.2f, 0.0f, 0.f, 0.0f, 0, 0);
    Rectangle hat2(clock_x-clock_width*0.25f, clock_y+clock_width*1.02f, clock_width*0.5f, clock_width*0.75f, 0.0f, 0.f, 0.0f, 0, 0);
    
    float bow_y = clock_y - clock_width*0.4f;
    // Bow
    Triangle t1(clock_x-clock_width*0.3f, bow_y-clock_width*0.15f, clock_x, bow_y, clock_x-clock_width*0.3f, bow_y+clock_width*0.15f, 0.16f, 0.27f, 0.73f, 0);
    Triangle t2(clock_x+clock_width*0.3f, bow_y-clock_width*0.15f, clock_x, bow_y, clock_x+clock_width*0.3f, bow_y+clock_width*0.15f, 0.16f, 0.27f, 0.73f, 0);
    Circle bow_circle1(clock_x, bow_y, clock_width*0.12f, 0.16f, 0.27f, 0.73f, 0.0f);

    // Butler Clock 2
    clock_x = 360.0f;
    // Body
    Circle clock_circle5(clock_x, clock_y, clock_width, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_hand3(clock_x+clock_width*1.05f, clock_y-clock_width/5, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_hand4(clock_x-clock_width*1.05f, clock_y-clock_width/5, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_foot3(clock_x+clock_width*0.4f, clock_y-clock_width*0.9f, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_foot4(clock_x-clock_width*0.4f, clock_y-clock_width*0.9f, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    // Circle clock_horn1(clock_x+clock_width, clock_y-clock_width*0.9f, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    // Circle clock_horn2(clock_x+clock_width, clock_y-clock_width*0.9f, clock_width/4, 0.79f, 0.83f, 0.88f, 0.0f);
    Circle clock_circle6(clock_x, clock_y, clock_width*0.85, 1.0f, 1.0f, 1.0f, 0.0f);
        
    // Clock Hands
    // Minute Hand
    Rectangle h4(clock_x-2.5f, clock_y, 5.0f, clock_width*0.6f, 0.215f, 0.215f, 0.215f, 12.0f / 720.0f, 3);
    // Hour Hand
    Rectangle h5(clock_x-2.0f, clock_y, 4.0f, clock_width*0.8f, 0.215f, 0.215f, 0.215f, 1.0f / 720.0f, 3);
    // Second Hand
    Rectangle h6(clock_x-1.0f, clock_y, 2.0f, clock_width*0.7f, 1.0f, 0.2f, 0.2f, 720.0f / 720.0f, 3);
    // Center Circle 1
    Circle clock_circle7(clock_x, clock_y, clock_width*0.1f, 0.215f, 0.215f, 0.215f, 0.0f);
    Circle clock_circle8(clock_x, clock_y, clock_width*0.05f, 1.0f, 1.0f, 1.0, 0.0f);
    
    // Hat
    Rectangle hat3(clock_x-clock_width*0.4f, clock_y+clock_width*1.02f, clock_width*0.8f, clock_width*0.2f, 0.0f, 0.f, 0.0f, 0, 0);
    Rectangle hat4(clock_x-clock_width*0.25f, clock_y+clock_width*1.02f, clock_width*0.5f, clock_width*0.75f, 0.0f, 0.f, 0.0f, 0, 0);
    
    // float bow_y = clock_y - clock_width*0.4f;
    // Bow
    Triangle t3(clock_x-clock_width*0.3f, bow_y-clock_width*0.15f, clock_x, bow_y, clock_x-clock_width*0.3f, bow_y+clock_width*0.15f, 0.73f, 0.27f, 0.16f, 0);
    Triangle t4(clock_x+clock_width*0.3f, bow_y-clock_width*0.15f, clock_x, bow_y, clock_x+clock_width*0.3f, bow_y+clock_width*0.15f, 0.73f, 0.27f, 0.16f, 0);
    Circle bow_circle2(clock_x, bow_y, clock_width*0.12f, 0.73f, 0.27f, 0.16f, 0.0f);

    
    addToVertices(&big_white);
    addToVertices(&bg_circle);
    addToVertices(&r1);
    addToVertices(&r2);
    addToVertices(&r3);
    addToVertices(&r4);
    addToVertices(&r5);
    addToVertices(&r6);
    addToVertices(&r7);
    addToVertices(&r8);
    addToVertices(&clock_hand1);
    addToVertices(&clock_hand2);
    addToVertices(&clock_foot1);
    addToVertices(&clock_foot2);
    addToVertices(&clock_circle1);
    addToVertices(&clock_circle2);
    addToVertices(&h1);
    addToVertices(&h2);
    addToVertices(&h3);
    addToVertices(&clock_circle3);
    addToVertices(&clock_circle4);
    addToVertices(&hat1);
    addToVertices(&hat2);
    addToVertices(&t1);
    addToVertices(&t2);
    addToVertices(&bow_circle1);

    addToVertices(&clock_hand3);
    addToVertices(&clock_hand4);
    addToVertices(&clock_foot3);
    addToVertices(&clock_foot4);
    addToVertices(&clock_circle5);
    addToVertices(&clock_circle6);
    addToVertices(&h4);
    addToVertices(&h5);
    addToVertices(&h6);
    addToVertices(&clock_circle7);
    addToVertices(&clock_circle8);
    addToVertices(&hat3);
    addToVertices(&hat4);
    addToVertices(&t3);
    addToVertices(&t4);
    addToVertices(&bow_circle2);
    std::vector<float> rotated_hand = r9.rotatedVertices(0.0f, 0.0f, 45.0f);
    vertices.insert(vertices.end(), rotated_hand.begin(), rotated_hand.end());
    
    addToVertices(&small_white);
    
    Star star1(175.0f, 175.0f, 25.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.5123124f);
    Star star2(-159.0f, 200.0f, 25.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.1938246f);
    Star star3(90.0f, -80.0f, 25.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.725091351f);
    
    addToVertices(&star1);
    addToVertices(&star2);
    addToVertices(&star3);

    // std::vector<float> star_vertices = star2.starVertices();

    // vertices.insert(vertices.end(), star_vertices.begin(), star_vertices.end());

    // for (int i = 0; i < circle_sides*3; i++) {
    //     int start = i*6;
    //     std::cout << vertices[start+0] << " " << vertices[start+1] << " "   << vertices[start+2] << " " << vertices[start+3] << " " << vertices[start+4] << " " << vertices[start+5] << std::endl;
    // }

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
