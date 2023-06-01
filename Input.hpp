#pragma once

#include "Common.hpp"

enum
{
    KC_LEFT = VK_LEFT,
    KC_RIGHT = VK_RIGHT,
    KC_UP = VK_UP,
    KC_DOWN = VK_DOWN,
    KC_ESCAPE = VK_ESCAPE,
    KC_W = 'W',
    KC_S = 'S',
    KC_A = 'A',
    KC_D = 'D',
    KC_Q = 'Q',
    KC_Z = 'Z'
};

class Input
{
public:
    static const int MAX_KEYS = 256;

    bool keys[MAX_KEYS];

    Input();
};
