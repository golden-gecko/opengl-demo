#include "Render.hpp"
#include "Texture.hpp"

void Texture::apply()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::generate()
{
    glGenTextures(1, &id);

    apply();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 128, 128, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
}

void Texture::generateNoise()
{
    for (int i = 0; i < 128 * 128; i++)
    {
        data[i] = static_cast<GLubyte>(getRandomColor(192, 216));
    }

    generate();
}

void Texture::generateRoad()
{
    for (int z = 0; z < 128; z++)
    {
        for (int x = 0; x < 128; x++)
        {
            data[z * 128 + x] = 0;

            if (x >= 54 && x <= 74)
            {
                data[z * 128 + x] = 255;
            }
        }
    }

    generate();
}
