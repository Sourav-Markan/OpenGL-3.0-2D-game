#include "magnet.h"
#include "main.h"
#include <stdlib.h>

Magnet::Magnet(float centerx, float centery, color_t color,float size)
{
    this->rotation = 0;
    this->position = glm::vec3(centerx, centery, 0);
    this->rotation = 0;

    // speedx = -0.01+(rand()/(float) RAND_MAX)*0.02;
    speedx = 0.0;
    speedy = 0.0;
    accx   = 0.0;
    accy   = 0.0;

    float r = size;

    int n=100,count=0;
    float radius=1,radius1=0.7;
    double anglechange=180;
    anglechange = 360/n;
    //4.0f=2.5;

    static GLfloat vertex_buffer_data[10000],vertex_buffer_data1[10000];
    for(int i=0;i<60;i++)
    {
        //1 coordinate
        float intial_angle = i*anglechange;
        vertex_buffer_data[count++]=centerx + radius*cos((intial_angle*3.14/180)+3.14/2);
        vertex_buffer_data[count++]=0.0f + radius*sin((intial_angle*3.14/180)+3.14/2);
        vertex_buffer_data[count++]=0.0f;
        //2 coordinate
        vertex_buffer_data[count++]=centerx;
        vertex_buffer_data[count++]=0.0f;
        vertex_buffer_data[count++]=0.0f;
        //3 coorinate
        intial_angle = (i+1)*anglechange;
        vertex_buffer_data[count++]=centerx +radius*cos((intial_angle*3.14/180)+3.14/2);
        vertex_buffer_data[count++]=0.0f + radius*sin((intial_angle*3.14/180)+3.14/2);
        vertex_buffer_data[count++]=0.0f;
     }
    for(int i=0;i<60;i++)
    {
        //1 coordinate
        float intial_angle = i*anglechange;
        vertex_buffer_data1[count++]=centerx + radius1*cos((intial_angle*3.14/180)+3.14/2);
        vertex_buffer_data1[count++]=0.0f + radius1*sin((intial_angle*3.14/180)+3.14/2);
        vertex_buffer_data1[count++]=0.0f;
        //2 coordinate
        vertex_buffer_data1[count++]=centerx;
        vertex_buffer_data1[count++]=0.0f;
        vertex_buffer_data1[count++]=0.0f;
        //3 coorinate
        intial_angle = (i+1)*anglechange;
        vertex_buffer_data1[count++]=centerx +radius1*cos((intial_angle*3.14/180)+3.14/2);
        vertex_buffer_data1[count++]=0.0f + radius1*sin((intial_angle*3.14/180)+3.14/2);
        vertex_buffer_data1[count++]=0.0f;
     }

    this->object = create3DObject(GL_TRIANGLES, 300, vertex_buffer_data, COLOR_MAGNET, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 600, vertex_buffer_data1, COLOR_BACKGROUND, GL_FILL);
}

void Magnet::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.8f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}


void Magnet::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}
bounding_box_t Magnet::bounding_box()
{
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
