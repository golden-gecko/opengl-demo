#pragma once

#include "Common.hpp"
#include "Object.hpp"
#include "Vector.hpp"

class Tree: public Object
{
public:
    void generate();
private:
    void _generate(const char* pattern, int depth, int maxDepth, const Vector<float>& position, const Vector<float>& angle);
};
