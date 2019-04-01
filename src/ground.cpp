#include "ground.h"
#include "main.h"

Ground::Ground(color_t color_bottom,color_t color_grass,color_t color_pond) {
//    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    static const GLfloat ground_brown[] = {
            -25, -25, 0, // vertex 1
             25,  -25, 0, // vertex 2
            -25,  -2.3, 0, // vertex 3

             25, -2.3, 0, // vertex 1
             25,  -25, 0, // vertex 2
            -25,  -2.3, 0, // vertex 3
        };

    static const GLfloat ground_grass[] = {
            -25, -2.3, 0, // vertex 1
             25,  -2.3, 0, // vertex 2
            -25,  -1.8, 0, // vertex 3

             25, -1.8, 0, // vertex 1
             25,  -2.3, 0, // vertex 2
            -25,  -1.8, 0, // vertex 3
        };

    this->object = create3DObject(GL_TRIANGLES, 6,ground_brown, color_bottom, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 6,ground_grass, color_grass, GL_FILL);

    int n=100,count=0;
    float radius=1;
    double anglechange=180;
    anglechange = 360/n;
    static GLfloat vertex_buffer_data[10000];
    for(int i=0;i<60;i++)
    {
        //1 coordinate
        float intial_angle = i*anglechange;
        vertex_buffer_data[count++]=radius*cos(intial_angle*3.14/180);
        vertex_buffer_data[count++]=-1.8 + radius*sin(intial_angle*-3.14/180);
        vertex_buffer_data[count++]=0.0f;
        //2 coordinate
        vertex_buffer_data[count++]=0.0f;
        vertex_buffer_data[count++]=-1.8f;
        vertex_buffer_data[count++]=0.0f;
        //3 coorinate
        intial_angle = (i+1)*anglechange;
        vertex_buffer_data[count++]=radius*cos(intial_angle*3.14/180);
        vertex_buffer_data[count++]=-1.8 + radius*sin(intial_angle*-3.14/180);
        vertex_buffer_data[count++]=0.0f;
     }
    this->object2 = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data, color_pond, GL_FILL);



}



void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}



// dont know
bounding_box_t Ground::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
