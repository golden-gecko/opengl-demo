#pragma once

#include "Common.hpp"
#include "Vector.hpp"

class Object
{
private:
    static const int MAX_ENABLE_FLAGS = 10;
public:
    GLenum enable[MAX_ENABLE_FLAGS];

    Vector<float> position;

    Vector<float>* colors;
    Vector<float>* normals;
    Vector2<float>* texCoords; // @todo change to vector2
    Vector<float>* vertices;

    Object();

    void createCube(const Vector<float>& color, const Vector<float>& position, const Vector<float>& scale);
    void createLine(const Vector<float>& color, const Vector<float>& v1, const Vector<float>& v2);
    void createQuad(const Vector<float>& color, const Vector<float>& normal, const Vector<float>& v1, const Vector<float>& v2);
    void createTriangle(const Vector<float>& color, const Vector<float>& normal, const Vector<float>& v1, const Vector<float>& v2, const Vector<float>& v3);

    void generate(GLenum operation, int size);
    void render();

#ifndef DISABLE_MEMORY_DEALLOCATION
    void destroy();
#endif
private:
    GLenum operation;

    int size;
    int maxSize;

    void resize(int newSize);
};
