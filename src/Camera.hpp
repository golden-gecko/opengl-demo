#pragma once

#include "Vector.hpp"

class Camera
{
public:
    Vector<float> eye;
    Vector<float> center;

    float yaw;
    float pitch;

    float speed;
    float angularSpeed;

    Camera();

    void move(bool keys[], float time);

    void apply();
};
