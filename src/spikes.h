#include "main.h"

#ifndef SPIKES_H
#define SPIKES_H


class Spikes {
public:
    Spikes() {}
    Spikes(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed_x,speed_y;
    double acc_x, acc_y;
    void change_speed();
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
};

#endif // SPIKES_H
