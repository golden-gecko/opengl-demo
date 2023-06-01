#include "Object.hpp"

Object::Object(): size(0), maxSize(0)
{
    memset(enable, 0, sizeof(GLenum) * MAX_ENABLE_FLAGS);
}

void Object::createCube(const Vector<float>& color, const Vector<float>& position, const Vector<float>& scale)
{
    resize(size + 24);

    auto nFront = Vector<float>(0.0f, 0.0f, 1.0f);
    auto nBack = Vector<float>(0.0f, 0.0f, -1.0f);
    auto nTop = Vector<float>(0.0f, 1.0f, 0.0f);
    auto nBottom = Vector<float>(0.0f, -1.0f, 0.0f);
    auto nRight = Vector<float>(1.0f, 0.0f, 0.0f);
    auto nLeft = Vector<float>(-1.0f, 0.0f, 0.0f);

    // Front.
    colors[size] = color;
    normals[size] = nFront;
    vertices[size] = Vector<float>(-0.5f, 0.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].y);
    size++;

    colors[size] = color;
    normals[size] = nFront;
    vertices[size] = Vector<float>(0.5f, 0.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].y);
    size++;

    colors[size] = color;
    normals[size] = nFront;
    vertices[size] = Vector<float>(0.5f, 1.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].y);
    size++;

    colors[size] = color;
    normals[size] = nFront;
    vertices[size] = Vector<float>(-0.5f, 1.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].y);
    size++;

    // Back.
    colors[size] = color;
    normals[size] = nBack;
    vertices[size] = Vector<float>(-0.5f, 0.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].y);
    size++;

    colors[size] = color;
    normals[size] = nBack;
    vertices[size] = Vector<float>(-0.5f, 1.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].y);
    size++;

    colors[size] = color;
    normals[size] = nBack;
    vertices[size] = Vector<float>(0.5f, 1.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].y);
    size++;

    colors[size] = color;
    normals[size] = nBack;
    vertices[size] = Vector<float>(0.5f, 0.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].y);
    size++;

    // Top.
    colors[size] = color;
    normals[size] = nTop;
    vertices[size] = Vector<float>(-0.5f, 1.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nTop;
    vertices[size] = Vector<float>(-0.5f, 1.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nTop;
    vertices[size] = Vector<float>(0.5f, 1.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nTop;
    vertices[size] = Vector<float>(0.5f, 1.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].z);
    size++;

    // Bottom.
    colors[size] = color;
    normals[size] = nBottom;
    vertices[size] = Vector<float>(-0.5f, 0.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nBottom;
    vertices[size] = Vector<float>(0.5f, 0.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nBottom;
    vertices[size] = Vector<float>(0.5f, 0.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nBottom;
    vertices[size] = Vector<float>(-0.5f, 0.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].x, vertices[size].z);
    size++;

    // Right.
    colors[size] = color;
    normals[size] = nRight;
    vertices[size] = Vector<float>(0.5f, 0.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].y, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nRight;
    vertices[size] = Vector<float>(0.5f, 1.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].y, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nRight;
    vertices[size] = Vector<float>(0.5f, 1.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].y, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nRight;
    vertices[size] = Vector<float>(0.5f, 0.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].y, vertices[size].z);
    size++;

    // Left.
    colors[size] = color;
    normals[size] = nLeft;
    vertices[size] = Vector<float>(-0.5f, 0.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].y, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nLeft;
    vertices[size] = Vector<float>(-0.5f, 0.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].y, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nLeft;
    vertices[size] = Vector<float>(-0.5f, 1.0f, 0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].y, vertices[size].z);
    size++;

    colors[size] = color;
    normals[size] = nLeft;
    vertices[size] = Vector<float>(-0.5f, 1.0f, -0.5f) * scale + position;
    texCoords[size] = Vector2<float>(vertices[size].y, vertices[size].z);
    size++;
}

void Object::createLine(const Vector<float>& color, const Vector<float>& v1, const Vector<float>& v2)
{
    resize(size + 2);

    colors[size] = color;
    vertices[size++] = v1;

    colors[size] = color;
    vertices[size++] = v2;
}

void Object::createQuad(const Vector<float>& color, const Vector<float>& normal, const Vector<float>& v1, const Vector<float>& v2)
{
    resize(size + 4);

    colors[size] = color;
    normals[size] = normal;
    texCoords[size] = Vector2<float>(v1.x, v1.z);
    vertices[size] = v1;
    size++;

    colors[size] = color;
    normals[size] = normal;
    texCoords[size] = Vector2<float>(v1.x, v2.z);
    vertices[size] = Vector<float>(v1.x, 0.0f, v2.z);
    size++;

    colors[size] = color;
    normals[size] = normal;
    texCoords[size] = Vector2<float>(v2.x, v2.z);
    vertices[size] = v2;
    size++;

    colors[size] = color;
    normals[size] = normal;
    texCoords[size] = Vector2<float>(v2.x, v1.z);
    vertices[size] = Vector<float>(v2.x, 0.0f, v1.z);
    size++;
}

void Object::createTriangle(const Vector<float>& color, const Vector<float>& normal, const Vector<float>& v1, const Vector<float>& v2, const Vector<float>& v3)
{
    resize(size + 6);

    colors[size] = color;
    normals[size] = normal;
    texCoords[size] = Vector2<float>(v1.x, v1.z);
    vertices[size] = v1;
    size++;

    colors[size] = color;
    normals[size] = normal;
    texCoords[size] = Vector2<float>(v2.x, v2.z);
    vertices[size] = v2;
    size++;

    colors[size] = color;
    normals[size] = normal;
    texCoords[size] = Vector2<float>(v3.x, v3.z);
    vertices[size] = v3;
    size++;
}

void Object::generate(GLenum operation, int size)
{
    this->operation = operation;

    resize(size);
}

void Object::render()
{
    for (int i = 0; i < MAX_ENABLE_FLAGS; i++)
    {
        if (enable[i] != 0)
        {
            glEnable(enable[i]);
        }
    }

    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, colors);
    glNormalPointer(GL_FLOAT, 0, normals);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawArrays(operation, 0, size);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();

    for (int i = 0; i < MAX_ENABLE_FLAGS; i++)
    {
        if (enable[i] != 0)
        {
            glDisable(enable[i]);
        }
    }
}

#ifndef DISABLE_MEMORY_DEALLOCATION
void Object::destroy()
{
    delete[] colors;
    delete[] normals;
    delete[] texCoords;
    delete[] vertices;
}
#endif

void Object::resize(int newSize)
{
    if (newSize > maxSize)
    {
        Vector<float>* newColors = new Vector<float>[newSize];
        Vector<float>* newNormals = new Vector<float>[newSize];
        Vector2<float>* newTexCoords = new Vector2<float>[newSize];
        Vector<float>* newVertices = new Vector<float>[newSize];

        if (maxSize)
        {
            memcpy(newColors, colors, sizeof(Vector<float>) * maxSize);
            memcpy(newNormals, normals, sizeof(Vector<float>) * maxSize);
            memcpy(newTexCoords, texCoords, sizeof(Vector2<float>) * maxSize);
            memcpy(newVertices, vertices, sizeof(Vector<float>) * maxSize);

            delete[] colors;
            delete[] normals;
            delete[] texCoords;
            delete[] vertices;
        }

        colors = newColors;
        normals = newNormals;
        texCoords = newTexCoords;
        vertices = newVertices;

        maxSize = newSize;
    }
}
