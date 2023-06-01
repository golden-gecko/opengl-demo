#pragma once

#include "Common.hpp"

class Texture
{
public:
    void apply();
    void generateNoise();
    void generateRoad();
private:
    GLuint id;
    GLubyte data[128 * 128];

    void generate();
};
