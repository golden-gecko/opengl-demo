#include "Math.hpp"
#include "Random.hpp"
#include "Render.hpp"
#include "Terrain.hpp"
#include "Tree.hpp"

extern Terrain* terrain;

void Tree::generate()
{
    Object::generate(GL_LINES, 10);

    position.x = static_cast<float>(random(terrain->size * terrain->scale));
    position.z = static_cast<float>(random(terrain->size * terrain->scale));

    position.y = terrain->getHeight(position.x, position.z);

    _generate("A", 1, 1, Vector<float>(0.0f, 0.0f, 0.0f), Vector<float>());

    position.x = 10.0f;
    position.y = 10.0f;
    position.z = 10.0f;
}

void Tree::_generate(const char* pattern, int depth, int maxDepth, const Vector<float>& position, const Vector<float>& angle)
{
    if (depth <= 0)
    {
        return;
    }

    for (int i = 0; pattern[i] != '\0'; i++)
    {
        char next[3] = { '\0', '\0', '\0' };

        if (pattern[i] == 'A')
        {
            next[0] = 'B';
        }
        else if (pattern[i] == 'B')
        {
            next[0] = 'C';
        }
        else if (pattern[i] == 'C')
        {
            next[0] = 'C';
            next[1] = 'D';
        }
        else if (pattern[i] == 'D')
        {
            next[0] = 'C';
        }

        // Render leaves. 
        /*
        if (depth == 1)
        {
            glPushMatrix();
            glTranslatef(0.0f, size, 0.0f);
            glEnable(GL_LIGHTING);
            renderCube();
            glDisable(GL_LIGHTING);
            glPopMatrix();
        }
        //*/

        float factor = 0.5f * depth / maxDepth;
        auto newPosition = Vector<float>(0.0f, 100.0f, 0.0f);

        Vector<float> newAngle;
        
        newAngle.x = (random(2) ? (-20 - random(10)) : (20 + random(10))) + angle.x;
        newAngle.y = (random(2) ? (-20 - random(10)) : (20 + random(10))) + angle.y;
        newAngle.z = (random(2) ? (-20 - random(10)) : (20 + random(10))) + angle.z;

        //if (pattern[i] == 'A' || pattern[i] == 'B')
        {
            newAngle = Vector<float>();
        }

        newAngle.x = 0.0f;
        newAngle.y = 0.0f;
        newAngle.z = 90.0f;

        auto sx = sin(Math::degToRad(newAngle.x));
        auto cx = cos(Math::degToRad(newAngle.x));

        auto sy = sin(Math::degToRad(newAngle.y));
        auto cy = cos(Math::degToRad(newAngle.y));

        auto sz = sin(Math::degToRad(newAngle.z));
        auto cz = cos(Math::degToRad(newAngle.z));

        float x = newPosition.x;
        float y = newPosition.y;
        float z = newPosition.z;

        // X
        x = x;
        y = y * sx - z * cx;
        z = y * cx + z * sx;

        // Y
        x =  x * cy + z * sy;
        y =  y;
        z = -x * sy + z * cy;

        // Z
        x = x * cz - y * sz;
        y = x * sz + y * cz;
        z = z;

        newPosition.x = x;
        newPosition.y = y;
        newPosition.z = z;

        createLine(Vector<float>(factor, 0.75f - factor, 0.0f), position, position + newPosition);

        _generate(next, depth - 1, maxDepth, position + newPosition, newAngle);
    }
}
