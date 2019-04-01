#include "balls.h"
#include "main.h"
#include "plank.h"

Balls::Balls(int type) {
    // give different range for different colour
    color_t color_ball;
    float x = RandomFloat(-60,20);
    float y = RandomFloat(0,6);
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_y = 0.0;
    typee = type;
    // Give speed according to color
    if(type == 0)
    {
        color_ball = COLOR_Yellow;
        speed_x = 0.04 ;
        radius=0.3;
    }
    if(type == 1)
    {
        color_ball = COLOR_WHITE;
        speed_x = 0.07 ;
        radius=0.2;
    }
    if(type == 2)
    {
        color_ball = COLOR_RED;
        speed_x = 0.1 ;
        radius=0.15;
    }
    corner_left = 1; // corner 0 for going right 1 for left
    corner_right = 1; // corner 1 for going right 0 for left
    int n=100,count=0;
    double anglechange=0;
    anglechange = 360/n;
    static GLfloat vertex_buffer_data[10000];
    for(int i=0;i<2*n;i++)
    {
        //1 coordinate
        float intial_angle = i*anglechange;
        vertex_buffer_data[count++]=radius*cos(intial_angle*3.14/180);
        vertex_buffer_data[count++]=radius*sin(intial_angle*3.14/180);
        vertex_buffer_data[count++]=0.0f;
        //2 coordinate
        vertex_buffer_data[count++]=0.0f;
        vertex_buffer_data[count++]=0.0f;
        vertex_buffer_data[count++]=0.0f;
        //3 coorinate
        intial_angle = (i+1)*anglechange;
        vertex_buffer_data[count++]=radius*cos(intial_angle*3.14/180);
        vertex_buffer_data[count++]=radius*sin(intial_angle*3.14/180);
        vertex_buffer_data[count++]=0.0f;
        printf ("%d\n",count);
     }
 //   plank       =Plank(ball1.position.x,ball1.position.y,COLOR_GREEN);

    this->object = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data, color_ball, GL_FILL);
}


void Balls::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Balls::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Balls::remove_ball(int i)
{
    this->position.x=35;
    this->position.y=35;
    this->speed_x=0;
    this->speed_y=0;
}

void Balls::tick()
{
    this->position.x += speed_x;
    if(this->position.x > 25)
        this->position.x=-25;
//    if((this->position.x < 4 or this->position.x < -4 ) and corner_right == 1 and corner_left == 0)
//    {
//        this->position.x += speed_x;
//    }
//    else
//    {
//        if(this->position.x <= -4)
//        {
//            corner_left = 0;
//            corner_right = 1;
//        }
//        if(this->position.x >= 4)
//        {
//            corner_left = 1;
//            corner_right = 0;
//        }
//        this->position.x -= speed_x;
//    }
//    this->position.y += speed_y;
}

bounding_box_t Balls::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
