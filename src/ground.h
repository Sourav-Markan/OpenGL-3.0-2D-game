#include "main.h"

#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground() {}
    Ground(color_t color_bottom,color_t color_grass,color_t color_pond);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void draw_grass(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // GROUND_H
