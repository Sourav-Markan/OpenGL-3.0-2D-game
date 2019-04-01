#include "spikes.h"
#include "main.h"
#include "math.h"

Spikes::Spikes(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_y = 0.0;
    acc_y = 0.0;
    speed_x = 0.02;
    acc_x = 0.0 ;

    int n=100,count=0;
    float radius=0.3;
    double anglechange=0;
    anglechange = 360/n;
    static GLfloat vertex_buffer_data[10000],vertex_buffer_data1[10000];
    for(int i=0;i<30;i++)
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
        //printf ("%d\n",count);
     }
    for(int i=0;i<30;i++)
    {
        //1 coordinate
        float intial_angle = i*anglechange;
        vertex_buffer_data1[count++]=radius*cos((intial_angle*3.14/180) + 3.14);
        vertex_buffer_data1[count++]=radius*sin((intial_angle*3.14/180) + 3.14);
        vertex_buffer_data1[count++]=0.0f;
        //2 coordinate
        vertex_buffer_data1[count++]=0.0f;
        vertex_buffer_data1[count++]=0.0f;
        vertex_buffer_data1[count++]=0.0f;
        //3 coorinate
        intial_angle = (i+1)*anglechange;
        vertex_buffer_data1[count++]=radius*cos((intial_angle*3.14/180) + 3.14);
        vertex_buffer_data1[count++]=radius*sin((intial_angle*3.14/180) + 3.14);
        vertex_buffer_data1[count++]=0.0f;

     }
    this->object = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data1, color, GL_FILL);
}


void Spikes::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Spikes::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Spikes::change_speed()
{
    speed_x  += acc_x ;
    speed_y  += acc_y;
}

void Spikes::tick()
{
   this->position.x += speed_x;
}

bounding_box_t Spikes::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.59, 0.59 };
    return bbox;
}
