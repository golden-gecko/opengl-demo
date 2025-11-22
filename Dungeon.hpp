#pragma once

#include "Common.hpp"
#include "Vector.hpp"

class Dungeon
{
public:
    Vector<unsigned char> size;

    Dungeon();

    void generate();

    void render();
};
