#include "Common.hpp"
#include "Random.hpp"
#include "Render.hpp"

int getRandomColor(int min, int max)
{
    return min + random(max - min);
}

void renderCube()
{
    glBegin(GL_QUADS);

    // Front.
    glNormal3f( 0.0f,  0.0f,  1.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);

    // Back.
    glNormal3f( 0.0f,  0.0f,  -1.0f);

    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

    // Top.
    glNormal3f( 0.0f,  1.0f,  0.0f);

    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);

    // Bottom.
    glNormal3f( 0.0f, -1.0f,  0.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);

    // Right.
    glNormal3f(1.0f,  0.0f,  0.0f);

    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);

    // Left.
    glNormal3f(-1.0f,  0.0f,  0.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

    glEnd();
}

void renderQuad(Vector<float>* normals, Vector<float>* vertices)
{
    glNormal3f(normals[0].x, normals[0].y, normals[0].z);

    glTexCoord2f(vertices[0].x, vertices[0].z);
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

    glTexCoord2f(vertices[1].x, vertices[1].z);
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

    glTexCoord2f(vertices[3].x, vertices[3].z);
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

    glNormal3f(normals[1].x, normals[1].y, normals[1].z);

    glTexCoord2f(vertices[3].x, vertices[3].z);
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

    glTexCoord2f(vertices[1].x, vertices[1].z);
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

    glTexCoord2f(vertices[2].x, vertices[2].z);
    glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
}
