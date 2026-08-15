#pragma once

#include "Object.hpp"
#include "Vector.hpp"

class Terrain: public Object
{
public:
    static const unsigned short size = 200;
    static const unsigned char scale = 10;

    Vector<float> map[size][size];
    Vector<float> normals[size - 1][size - 1][2];

    bool renderNormals;

    Terrain();

    void generate();
    float getHeight(float x, float z);
    void render();
};
