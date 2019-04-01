#include "plank.h"
#include "main.h"

Plank::Plank(float x,float y,color_t color) {
    this->position.x=x;
    this->position.y=y;
    this->speed_x=.1;
    //x=3;y=4;
    std::cout << x << y;
    static const GLfloat plank[] = {
            -1+x, -2+y+1, 0, // vertex 1
             1+x,  -2+y+1, 0, // vertex 2
            -1+x,  -2.3+y+1, 0, // vertex 3

             1+x, -2.3+y+1, 0, // vertex 1
             1+x,  -2+y+1, 0, // vertex 2
            -1+x,  -2.3+y+1, 0, // vertex 3
        };
        this->object = create3DObject(GL_TRIANGLES, 6,plank, COLOR_Ball, GL_FILL);
}
void Plank::tick() {

    this->position.x -= speed_x;
}

void Plank::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Plank::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
