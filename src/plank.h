#include "main.h"

#ifndef Plank_H
#define Plank_H


class Plank {
public:
    Plank() {}
    Plank(float x,float y,color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    int typee;
    void draw(glm::mat4 VP);
    void remove_ball(int i);
    void set_position(float x, float y);
    void tick();
    double speed_x,speed_y;
    void change_speed();
    int corner_left;
    int corner_right;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Plank_H
