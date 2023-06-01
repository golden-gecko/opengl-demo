#include "City.hpp"
#include "Common.hpp"
#include "Random.hpp"
#include "Render.hpp"
#include "Terrain.hpp"
#include "Vector.hpp"

extern Terrain* terrain;

City::City()
{
    road = 20.0f;
}

void City::generate()
{
    float offset = (terrain->size * terrain->scale - size) / 2.0f;

    position.x = offset;
    position.y = 70.0f;
    position.z = offset;

    Vector<float> area[2] =
    {
        Vector<float>(),
        Vector<float>(size, 0.0f, size)
    };

    // Split area into buildings and roads.
    split(area, 20);

    // Generate.
    Object::generate(GL_QUADS, 10);
    enable[0] = GL_LIGHTING;
    enable[1] = GL_TEXTURE_2D;

    texture.generateRoad();
}

void City::createBuilding(const Vector<float>* quads)
{
    Vector<float> position((quads[0] + quads[1]) / 2.0f);
    Vector<float> scale(quads[0] - quads[1]);

    scale.makeAbsolute();

    scale.x -= road;
    scale.y = 0.5f;
    scale.z -= road;

    if (random(10) == 0)
    {
        // Create park.
        createCube(Vector<float>(0.2f, 0.8f, 0.2f), position, scale);
    }
    else
    {
        // Create building.
        auto color = getRandomColor(128, 255);
        auto colorVector = Vector<float>(color / 255.0f, color / 255.0f, color / 255.0f);

        createCube(colorVector, position, scale);

        // Create upper parts of building.
        for (int j = 0; j < 3; j++)
        {
            if (j == 0 || random(4) == 0)
            {
                scale.x -= road;
                scale.y += road + static_cast<float>(random(20 * (j + 1)));
                scale.z -= road;

                createCube(colorVector, position, scale);
            }
        }
    }

    // Lights.
    auto color1 = Vector<float>(0.2f, 0.2f, 0.2f);
    auto color2 = Vector<float>(1.0f, 1.0f, 0.0f);

    auto scale1 = Vector<float>(0.5f, 10.0f, 0.5f);
    auto scale2 = Vector<float>(1.0f, 1.0f, 1.0f);

    auto offset = road * 0.6f;

    createCube(color1, Vector<float>(quads[0].x + offset, quads[0].y,         quads[0].z + offset), scale1);
    createCube(color2, Vector<float>(quads[0].x + offset, quads[0].y + 10.0f, quads[0].z + offset), scale2);

    createCube(color1, Vector<float>(quads[1].x - offset, quads[0].y,         quads[0].z + offset), scale1);
    createCube(color2, Vector<float>(quads[1].x - offset, quads[0].y + 10.0f, quads[0].z + offset), scale2);

    createCube(color1, Vector<float>(quads[1].x - offset, quads[0].y,         quads[1].z - offset), scale1);
    createCube(color2, Vector<float>(quads[1].x - offset, quads[0].y + 10.0f, quads[1].z - offset), scale2);

    createCube(color1, Vector<float>(quads[0].x + offset, quads[0].y,         quads[1].z - offset), scale1);
    createCube(color2, Vector<float>(quads[0].x + offset, quads[0].y + 10.0f, quads[1].z - offset), scale2);
}

void City::createRoad(const Vector<float>* lines)
{
    auto color = Vector<float>(1.0f, 1.0f, 1.0f);
    auto normal = Vector<float>(0.0f, 1.0f, 0.0f);

    float offset = road / 2.0f;

    float x = abs(lines[0].x - lines[1].x);
    float z = abs(lines[0].z - lines[1].z);

    auto v1 = Vector<float>(lines[0].x - offset, lines[0].y, lines[0].z + offset);
    auto v2 = Vector<float>(lines[1].x + offset, lines[1].y, lines[1].z - offset);

    if (x > z)
    {
        v1 = Vector<float>(lines[0].x + offset, lines[0].y, lines[0].z - offset);
        v2 = Vector<float>(lines[1].x - offset, lines[1].y, lines[1].z + offset);
    }

    createQuad(color, normal, v1, v2);
}

bool City::split(Vector<float> area[2], int depth)
{
    if (depth <= 0)
    {
        return false;
    }

    float margin = road * 4.0f;

    // If building is too small, do not split.
    float x = abs(area[1].x - area[0].x);
    float z = abs(area[1].z - area[0].z);

    if (x <= margin || z <= margin)
    {
        return false;
    }

    Vector<float> result[2][2] = { { area[0], area[1] }, { area[0], area[1] } };
    Vector<float> lines[2] = { area[0], area[1] };
    Vector<float> quads[2];

    if (x > z)
    {
        float size = x - margin * 2.0f;

        if (size <= margin)
        {
            return false;
        }

        float position = static_cast<float>(random(static_cast<int>(size))) + area[0].x + margin;

        result[0][1].x = position;
        result[1][0].x = position;

        lines[0].x = position;
        lines[1].x = position;

        createRoad(lines);

        if (split(result[0], depth - 1) == false)
        {
            quads[0] = area[0];
            quads[1].x = position;
            quads[1].z = area[1].z;

            createBuilding(quads);
        }

        if (split(result[1], depth - 1) == false)
        {
            quads[0].x = position;
            quads[0].z = area[0].z;
            quads[1] = area[1];

            createBuilding(quads);
        }
    }
    else
    {
        float size = z - margin * 2.0f;

        if (size <= margin)
        {
            return false;
        }

        float position = static_cast<float>(random(static_cast<int>(size))) + area[0].z + margin;

        result[0][1].z = position;
        result[1][0].z = position;

        lines[0].z = position;
        lines[1].z = position;

        createRoad(lines);

        if (split(result[0], depth - 1) == false)
        {
            quads[0] = area[0];
            quads[1].x = area[1].x;
            quads[1].z = position;

            createBuilding(quads);
        }

        if (split(result[1], depth - 1) == false)
        {
            quads[0].x = area[0].x;
            quads[0].z = position;
            quads[1] = area[1];

            createBuilding(quads);
        }
    }

    return true;
}
