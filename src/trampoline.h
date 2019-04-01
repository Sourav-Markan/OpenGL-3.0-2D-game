#include "main.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

class Trampoline {
public:
    Trampoline() {}
    Trampoline(float x, float y, color_t color,float size);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double speed_x,speed_y;
    double acc_x, acc_y;
    void change_speed();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // TRAMPOLINE_H
