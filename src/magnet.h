#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color,float size);
    glm::vec3 position;
    float rotation;
    float centerx,centery;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    double speedx,speedy;
    double accx, accy;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
};

#endif // MAGNET_H
