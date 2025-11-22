#pragma once

#include "Common.hpp"
#include "Object.hpp"
#include "Texture.hpp"
#include "Vector.hpp"

class City: public Object
{
public:
    static const unsigned short size = 1000;

    float road;

    City();
    void generate();
private:
    Texture texture;

    void createBuilding(const Vector<float>* quads);
    void createRoad(const Vector<float>* lines);
    bool split(Vector<float> area[2], int depth);
};
