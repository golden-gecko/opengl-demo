#include "Camera.hpp"
#include "Common.hpp"
#include "Input.hpp"
#include "Math.hpp"

Camera::Camera()
{
    eye.x = 500.0f;
    eye.y = 500.0f;
    eye.z = 500.0f;

    yaw = 45.0f;
    pitch = 215.0f;

    center.x = eye.x - sin(Math::degToRad(yaw)) * 10.0f;
    center.y = eye.y - tan(Math::degToRad(pitch)) * 10.0f;
    center.z = eye.z - cos(Math::degToRad(yaw)) * 10.0f;

    speed = 500.0f;
    angularSpeed = 45.0f;
}

void Camera::move(bool keys[], float time)
{
    float currentSpeed = speed * time;
    float currentAngularSpeed = angularSpeed * time;

    if (keys[KC_LEFT] == true)
    {
        yaw += currentAngularSpeed;
    }
    else if (keys[KC_RIGHT] == true)
    {
        yaw -= currentAngularSpeed;
    }

    if (keys[KC_UP] == true)
    {
        pitch += currentAngularSpeed;
    }
    else if (keys[KC_DOWN] == true)
    {
        pitch -= currentAngularSpeed;
    }

    float yawDeg = Math::degToRad(yaw);

    float sinYaw = sin(yawDeg);
    float cosYaw = cos(yawDeg);
    float sinYawSpeed = sinYaw * currentSpeed;
    float cosYawSpeed = cosYaw * currentSpeed;

    if (keys[KC_W] == true)
    {
        eye.x -= sinYawSpeed;
        eye.z -= cosYawSpeed;
    }
    else if (keys[KC_S] == true)
    {
        eye.x += sinYawSpeed;
        eye.z += cosYawSpeed;
    }

    float yawStrafeDeg = Math::degToRad(yaw + 90.0f);
    float sinYawStrafeSpeed = sin(yawStrafeDeg) * currentSpeed;
    float cosYawStrafeSpeed = cos(yawStrafeDeg) * currentSpeed;

    if (keys[KC_A] == true)
    {
        eye.x -= sinYawStrafeSpeed;
        eye.z -= cosYawStrafeSpeed;
    }
    else if (keys[KC_D] == true)
    {
        eye.x += sinYawStrafeSpeed;
        eye.z += cosYawStrafeSpeed;
    }

    if (keys[KC_Q] == true)
    {
        eye.y += currentSpeed;
    }
    else if (keys[KC_Z] == true)
    {
        eye.y -= currentSpeed;
    }

    center.x = eye.x - sinYaw * 10.0f;
    center.y = eye.y - tan(Math::degToRad(pitch)) * 10.0f;
    center.z = eye.z - cosYaw * 10.0f;
}

void Camera::apply()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, 0.0f, 1.0f, 0.0f);
}
