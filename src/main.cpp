#include "main.h"
#include "timer.h"
#include "ball.h"
#include "balls.h"
#include "ground.h"
#include "trampoline.h"
#include "magnet.h"
#include "spikes.h"
#include "plank.h"
#include <string>
#define total_balls 50

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
bool moveup;
float ground_level;
/**************************
* Customizable functions *
**************************/
char a[100];
Ball ball1;
Timer t1(2.7);
Timer t2(8.2);
int score=0;
int life=5;
Balls balls[total_balls];
Ground ground;
Trampoline trampoline;
Magnet magnet;
Spikes spikes[15];
glm::vec3 eye,up,target;
//Plank plank[10];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

float RandomFloat(float min, float max)
{
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!

    eye.x=0;eye.y=0;eye.z=3;
    target.x=0;target.y=0;target.z=0;
    up.x=0;up.y=1;up.z=0;

    if(ball1.position.x <= -1)
        eye.x = target.x = ball1.position.x + 1;
    else if(ball1.position.x >= 1)
        eye.x = target.x = ball1.position.x - 1;
    else
        eye.x = target.x = 0;
    screen_zoom = 1.2/(ball1.position.y + 4) + 0.56;
    eye.y = target.y = ball1.position.y/3 - 0.32;

    if(abs(ball1.speed_y) > 0.03 && screen_zoom > 0.5)
        screen_zoom -= 0.0005;
    else if(screen_zoom < 1)
        screen_zoom += 0.0005;
    reset_screen();

    Matrices.view = glm::lookAt(eye, target, glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ground.draw(VP);
    trampoline.draw(VP);
    magnet.draw(VP);
    for (int i=0;i<15;i++)
        spikes[i].draw(VP);
    ball1.draw(VP);
    for (int i=0;i<total_balls;i++)
        balls[i].draw(VP);
//    for (int i=0;i<5;i++)
//        plank[1].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down  = glfwGetKey(window, GLFW_KEY_DOWN);
    for (int i=0;i<15;i++)
        if (detect_collision(ball1.bounding_box(),spikes[i].bounding_box()))
        {
            ball1.acc_y = 0;
            ball1.speed_y =0;
            return;
        }
    if (left) {
         ball1.set_position(ball1.position.x-0.1,ball1.position.y);
        if(detect_trampoline(ball1.bounding_box()))
        {
                ball1.set_position(ball1.position.x+0.1f,ball1.position.y);
        }
    }
    if (right)
    {
        ball1.set_position(ball1.position.x+0.1,ball1.position.y);
        if(detect_trampoline(ball1.bounding_box()))
        {
                ball1.set_position(ball1.position.x-0.1f,ball1.position.y);
        }
    }
    if (up )
    {
        ball1.acc_y = -0.005;
        if (detect_on_ground((ball1.bounding_box())))
             ball1.speed_y = 0.2;
     }
}

void tick_elements() {
    for (int i=0;i<total_balls;i++)
        balls[i].tick();
    for (int i=0;i<15;i++)
        spikes[i].tick();
    ball1.tick();
    if(ball1.position.x <= .8 && ball1.position.x >= 0)
    {
        ball1.position.x += -0.01;
    }
    if(ball1.position.x >= -.8 && ball1.position.x <= 0)
    {
        ball1.position.x += 0.01;
    }

   if (magnet_range(ball1.bounding_box()))
    {
       if(magnet.position.x >0 && magnet.position.x != -25 && !detect_on_ground((ball1.bounding_box())))
        ball1.position.x += 0.04;
       if(magnet.position.x <0 && magnet.position.x != -25 && !detect_on_ground((ball1.bounding_box())))
        ball1.position.x += -0.04;
    }
   if (detect_col_ball(ball1.bounding_box()))
     {
        if(ball1.position.y >=16)
            ball1.speed_y = -ball1.speed_y;
        ball1.speed_x = -ball1.speed_x;
        if(ball1.position.x <= -16)
            ball1.position.x = 16;
        if(ball1.position.x >= 16)
            ball1.position.x = -16;
     }
   for(int i=0;i<15;i++)
        if (detect_col_ball(spikes[i].bounding_box()))
        {
            //ball1.speed_x = -ball1.speed_x;
            if(spikes[i].position.x <= -16)
                spikes[i].position.x = 16;
            if(spikes[i].position.x >= 16)
                spikes[i].position.x = -16;
        }
    if(detect_trampoline(ball1.bounding_box()))
    {
        ball1.speed_y += 0.4;
    }
    if (detect_on_ground(ball1.bounding_box()))
    {
        ball1.acc_y = 0.0;
        ball1.speed_y = 0.0;
        ball1.set_position(ball1.position.x,-1.5);
    }

    for(int i=0;i<total_balls;i++)
    {
        if (detect_collision(ball1.bounding_box(), balls[i].bounding_box()))
        {
            if(-0.02 < ball1.speed_x && ball1.speed_x < .02 && ball1.speed_y<0)
            {
                ball1.speed_y = .13;
                ball1.speed_x = ball1.speed_x;
                balls[i].remove_ball(i);
                score += balls[i].typee + 1;
                sprintf(a,"SCORE : %d",score);
                glfwSetWindowTitle(window,a);
            }
        }
    }

    for (int j=0;j<15;j++)
    {
        if (detect_collision(ball1.bounding_box(), spikes[j].bounding_box()))
        {
            life--;
            score=score-10;

            sprintf(a,"SCORE : %d",score);
            glfwSetWindowTitle(window,a);
            //cout << "Remaining Life" << life;
            ball1.set_position(2,1.5);
            ball1.acc_y = -0.005;
            ball1.speed_y = 0.1;
            if(life==0)
            {

                cout << score << endl;
                for (int i=0;i<total_balls;i++)
                {
                    balls[i].speed_x=0;
                }
                for (int i=0;i<15;i++)
                    spikes[i].speed_x=0;
                ball1.speed_y = 0;
                ball1.speed_x = 0;
                ball1.set_position(3.7,-1.5);
                quit(window);
            }
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models(

    ground      = Ground(COLOR_GROUND,COLOR_GREEN,COLOR_POND);
    trampoline  = Trampoline(2.1,2.5,COLOR_TRAPOLINE,0.5);
    magnet      = Magnet(2,2,COLOR_RED,0.5);
    ball1       = Ball(1, 1.5, COLOR_Ball);

    ball1.speed_y = -0.1;
    for (int i=0;i<15;i++)
    {
        float x = RandomFloat(-40,9);
        spikes[i]      = Spikes(x,-1.5,COLOR_Spike);
    }
    int j=0;
    for (int i=0;i<total_balls;)
    {
        if(i<total_balls) balls[i++]     = Balls(0);
        if(i<total_balls) balls[i++]     = Balls(0);
        if(i<total_balls) balls[i++]     = Balls(1);
        if(i<total_balls) balls[i++]     = Balls(1);
        if(i<total_balls) balls[i++]     = Balls(2);
//       if(j<7 && i%10==0)
//        {
//            plank[j++]  =Plank(balls[i].position.x,balls[i].position.y,COLOR_GREEN);
//        }
    }

    //Spikes.speed = -ball2.speed;
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "SCORE : ";
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        if (t1.processTick()) {
           magnet.position.x = -25;
        }
        if(t2.processTick()){
            int yum = rand()%2;
            if(yum){
                magnet.rotation = 0;
                magnet.position.x = -3.4;
            }
            else
            {
                magnet.position.x = 8.5;
                magnet.rotation = 180;
            }

        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
        //cout << score;
    }
    cout << score;
    quit(window);
    cout << score;
}

bool detect_trampoline(const bounding_box_t &a)
{
        return ((a.x >= 2.7f and a.x <= 4.8f and a.y <= -0.1f)  );
}

bool detect_col_ball( const bounding_box_t &a)
{
    return (abs(a.y)>=16 or a.x > 16 or a.x <= -16);
}
bool detect_on_ground(const bounding_box_t &a)
{
    float grd;
    grd = - sqrt(1-(a.x*a.x))-1.5;
    if(a.x > .8 or a.x < -.8)
        return a.y<=-1.5;
    if(a.x <= .8 and a.x >= -.8)
    {
        float grd;
        grd = - sqrt(1-(a.x*a.x))-1.5;
        return a.y<=grd;
    }
}

bool detect_on_pond(const bounding_box_t &a)
{
    if(a.x <= .8 && a.x >= -.8)
        return a.y <= -10;
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return ((abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)));
}

bool magnet_range(const bounding_box_t &a)
{
   return(2<a.y<4);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
