#include "Camera.hpp"
#include "City.hpp"
#include "Common.hpp"
#include "Debug.hpp"
#include "Input.hpp"
#include "Random.hpp"
#include "Render.hpp"
#include "Terrain.hpp"
#include "Texture.hpp"
#include "Tree.hpp"
#include "Water.hpp"
#include "Window.hpp"

Camera* camera;
City* city;
Debug* debug;
Input* input;
Terrain* terrain;
Texture* texture;
Tree* trees;
Water* water;
Window* window;

static const int treeCount = 1;

void render(float time)
{
    // Input.
    camera->move(input->keys, time);

    // Projection.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1366.0f / 768.0f, 10.0f, 10000.0f);

    camera->apply();

    // Render.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->apply();
    debug->render();
    terrain->render();
    city->render();
    water->render(time);

    // Trees.
    for (int i = 0; i < treeCount; i++)
    {
        trees[i].render();
    }

    // Grass.
    /*
    srand(0);

    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);

    for (int i = 0; i < 1000; i++)
    {
        float x = static_cast<float>(random(1000));
        float z = static_cast<float>(random(1000));

        glPushMatrix();
        glTranslatef(x, terrain->getHeight(x, z), z);
        glRotatef(static_cast<float>(random(360)), 0.0f, 1.0f, 0.0f);
        glScalef(static_cast<float>(2 + random(10)), static_cast<float>(2 + random(10)), static_cast<float>(2 + random(10)));
        glBegin(GL_QUADS);
        glColor3f(0.0f, static_cast<float>(getRandomColor(128, 255)) / 255.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();
        glPopMatrix();
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    */

    glFlush();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        case WM_KEYDOWN:
            switch (wparam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    break;

                case 'N':
                    terrain->renderNormals = !(terrain->renderNormals);
                    break;

                case 'P':
                    static GLenum polygonMode = GL_FILL;

                    switch (polygonMode)
                    {
                        case GL_LINE:
                            polygonMode = GL_FILL;
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            break;

                        case GL_FILL:
                            polygonMode = GL_LINE;
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            break;
                    }
                    break;
            }

            if (wparam < 256)
            {
                input->keys[wparam] = true;
            }
            break;

        case WM_KEYUP:
            if (wparam < 256)
            {
                input->keys[wparam] = false;
            }
            break;

        case WM_SIZE:
            glViewport(0, 0, LOWORD(lparam), HIWORD(lparam));
            break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

int main()
{
    srand(GetTickCount());

    camera = new Camera();
    city = new City();
    debug = new Debug();
    input = new Input();
    terrain = new Terrain();
    texture = new Texture();
    trees = new Tree[treeCount];
    water = new Water();
    window = new Window();

    window->init();
    city->generate();
    debug->generate();
    terrain->generate();
    texture->generateNoise();

    for (int i = 0; i < treeCount; i++)
    {
        trees[i].generate();
    }

    DWORD last = GetTickCount();
    MSG msg;

    do
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            DWORD current = GetTickCount();
            float delta = (current - last) / 1000.0f;
            last = current;

            render(delta);
            SwapBuffers(window->hdc);
        }
    }
    while (msg.message != WM_QUIT);

#ifndef DISABLE_MEMORY_DEALLOCATION
    debug->destroy();
    window->destroy();

    delete camera;
    delete city;
    delete debug;
    delete input;
    delete terrain;
    delete texture;
    delete[] trees;
    delete water;
    delete window;
#endif

    return 0;
}
