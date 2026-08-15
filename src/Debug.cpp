#include "Common.hpp"
#include "Debug.hpp"

void Debug::generate()
{
    Object::generate(GL_LINES, 6);

    auto zero = Vector<float>(0.0f, 0.0f, 0.0f);

    createLine(Vector<float>(1.0f, 0.0f, 0.0f), zero, Vector<float>(100.0f, 0.0f, 0.0f));
    createLine(Vector<float>(0.0f, 1.0f, 0.0f), zero, Vector<float>(0.0f, 100.0f, 0.0f));
    createLine(Vector<float>(0.0f, 0.0f, 1.0f), zero, Vector<float>(0.0f, 0.0f, 100.0f));
}
