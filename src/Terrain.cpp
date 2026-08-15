#include "Common.hpp"
#include "Random.hpp"
#include "Render.hpp"
#include "Terrain.hpp"

Terrain::Terrain() : renderNormals(false)
{
}

void Terrain::generate()
{
    // Generate vertices.
    for (int z = 0; z < size; z++)
    {
        for (int x = 0; x < size; x++)
        {
            map[x][z].x = static_cast<float>(x * scale);
            map[x][z].y = static_cast<float>(random(100));
            map[x][z].z = static_cast<float>(z * scale);
        }
    }

    // Smooth vertices.
    static const int indices[9][2] =
    {
        { -1, -1 },
        { -1,  0 },
        { -1, +1 },
        {  0, -1 },
        {  0,  0 },
        {  0, +1 },
        { +1, -1 },
        { +1,  0 },
        { +1  +1 }
    };

    for (int pass = 0; pass < 2; pass++)
    {
        for (int z = 0; z < size; z++)
        {
            for (int x = 0; x < size; x++)
            {
                int count = 0;
                float sum = 0.0f;

                for (int i = 0; i < 9; i++)
                {
                    int xx = x + indices[i][0];
                    int zz = z + indices[i][1];

                    if (xx < 0 || xx > size - 1 || zz < 0 || zz > size - 1)
                    {
                        continue;
                    }

                    sum += map[xx][z + indices[i][1]].y;
                    count++;
                }

                map[x][z].y = sum / static_cast<float>(count);
            }
        }
    }

    Object::generate(GL_TRIANGLES, (size - 1) * (size - 1) * 6);

    enable[0] = GL_LIGHTING;
    enable[1] = GL_TEXTURE_2D;

    auto color = Vector<float>(0.0f, 1.0f, 0.0f);

    for (int z = 0; z < size - 1; z++)
    {
        for (int x = 0; x < size - 1; x++)
        {
            Vector<float> vertices[4] =
            {
                Vector<float>(map[x    ][z    ].x, map[x    ][z    ].y, map[x    ][z    ].z),
                Vector<float>(map[x    ][z + 1].x, map[x    ][z + 1].y, map[x    ][z + 1].z),
                Vector<float>(map[x + 1][z + 1].x, map[x + 1][z + 1].y, map[x + 1][z + 1].z),
                Vector<float>(map[x + 1][z    ].x, map[x + 1][z    ].y, map[x + 1][z    ].z)
            };

            Vector<float> v1(vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y, vertices[1].z - vertices[0].z);
            Vector<float> v2(vertices[3].x - vertices[0].x, vertices[3].y - vertices[0].y, vertices[3].z - vertices[0].z);

            Vector<float> v(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);

            float vl = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

            normals[x][z][0].x = v.x /vl;
            normals[x][z][0].y = v.y /vl;
            normals[x][z][0].z = v.z /vl;

            v1.x = vertices[1].x - vertices[3].x;
            v1.y = vertices[1].y - vertices[3].y;
            v1.z = vertices[1].z - vertices[3].z;

            v2.x = vertices[2].x - vertices[3].x;
            v2.y = vertices[2].y - vertices[3].y;
            v2.z = vertices[2].z - vertices[3].z;

            v.x = v1.y * v2.z - v1.z * v2.y;
            v.y = v1.z * v2.x - v1.x * v2.z;
            v.z = v1.x * v2.y - v1.y * v2.x;

            vl = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

            normals[x][z][1].x = v.x /vl;
            normals[x][z][1].y = v.y /vl;
            normals[x][z][1].z = v.z /vl;
        }
    }

    for (int z = 0; z < size - 1; z++)
    {
        for (int x = 0; x < size - 1; x++)
        {
            createTriangle(color, normals[x][z][0], map[x][z], map[x][z + 1], map[x + 1][z]);
            createTriangle(color, normals[x][z][0], map[x + 1][z], map[x][z + 1], map[x + 1][z + 1]);
        }
    }
}

float Terrain::getHeight(float x, float z)
{
    x /= static_cast<float>(scale);
    z /= static_cast<float>(scale);

    return map[static_cast<int>(x)][static_cast<int>(z)].y;
}

void Terrain::render()
{
    Object::render();

    if (renderNormals == true)
    {
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);

        for (int z = 0; z < size - 1; z++)
        {
            for (int x = 0; x < size - 1; x++)
            {
                float scaleF = static_cast<float>(scale);

                Vector<float> vertices[4] =
                {
                    Vector<float>( x      * scaleF, map[x    ][z    ].y,  z      * scaleF),
                    Vector<float>( x      * scaleF, map[x    ][z + 1].y, (z + 1) * scaleF),
                    Vector<float>((x + 1) * scaleF, map[x + 1][z + 1].y, (z + 1) * scaleF),
                    Vector<float>((x + 1) * scaleF, map[x + 1][z    ].y,  z      * scaleF)
                };

                for (int i = 0; i < 4; i++)
                {
                    float size = 2.0f;

                    float tx = (vertices[0].x + vertices[1].x + vertices[3].x) / 3.0f;
                    float ty = (vertices[0].y + vertices[1].y + vertices[3].y) / 3.0f;
                    float tz = (vertices[0].z + vertices[1].z + vertices[3].z) / 3.0f;

                    glVertex3f(tx, ty, tz);
                    glVertex3f(tx + normals[x][z][0].x * size, ty + normals[x][z][0].y * size, tz + normals[x][z][0].z * size);

                    tx = (vertices[3].x + vertices[1].x + vertices[2].x) / 3.0f;
                    ty = (vertices[3].y + vertices[1].y + vertices[2].y) / 3.0f;
                    tz = (vertices[3].z + vertices[1].z + vertices[2].z) / 3.0f;

                    glVertex3f(tx, ty, tz);
                    glVertex3f(tx + normals[x][z][1].x * size, ty + normals[x][z][1].y * size, tz + normals[x][z][1].z * size);
                }
            }
        }

        glEnd();
    }
}
