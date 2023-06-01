#pragma once

#include "Common.hpp"

class Window
{
public:
    WNDCLASS wc;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;

    void init();

#ifndef DISABLE_MEMORY_DEALLOCATION
    void destroy();
#endif
};
