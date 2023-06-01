#include "Common.hpp"
#include "Render.hpp"
#include "Terrain.hpp"
#include "Water.hpp"

extern Terrain* terrain;

Water::Water()
{
    scale = 10.0f;
    level = 30.0f;

    waveHeightMin = -2.0f;
    waveHeightMax = 2.0f;

    waveSpeed = 1.5f;
    waveHeight = waveHeightMin;
}

void Water::render(float time)
{
    glEnable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.5f, 0.75f);

    // Waves.
    if (waveHeight <= waveHeightMin || waveHeight >= waveHeightMax)
    {
        waveSpeed *= -1.0f;
    }

    waveHeight += waveSpeed * time;

    for (int z = 0; z < terrain->size - 1; z++)
    {
        for (int x = 0; x < terrain->size - 1; x++)
        {
            float sinX = static_cast<float>(sin(x));
            float sinZ = static_cast<float>(sin(z));

            float sinX1 = static_cast<float>(sin(x + 1));
            float sinZ1 = static_cast<float>(sin(z + 1));

            // Vertices.
            Vector<float> vertices[4] =
            {
                Vector<float>( x      * scale, level + sinX  * sinZ  * waveHeight,  z      * scale),
                Vector<float>( x      * scale, level + sinX  * sinZ1 * waveHeight, (z + 1) * scale),
                Vector<float>((x + 1) * scale, level + sinX1 * sinZ1 * waveHeight, (z + 1) * scale),
                Vector<float>((x + 1) * scale, level + sinX1 * sinZ  * waveHeight,  z      * scale)
            };

            // Normals.
            Vector<float> v1(vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y, vertices[1].z - vertices[0].z);
            Vector<float> v2(vertices[3].x - vertices[0].x, vertices[3].y - vertices[0].y, vertices[3].z - vertices[0].z);

            Vector<float> v(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);

            float vl = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
            Vector<float> normals[2];

            normals[0].x = v.x /vl;
            normals[0].y = v.y /vl;
            normals[0].z = v.z /vl;

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

            normals[1].x = v.x /vl;
            normals[1].y = v.y /vl;
            normals[1].z = v.z /vl;

            // Render.
            renderQuad(normals, vertices);
        }
    }

    glEnd();
    glDisable(GL_LIGHTING);
}
