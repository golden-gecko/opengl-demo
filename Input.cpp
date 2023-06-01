#include "Input.hpp"

Input::Input()
{
    memset(keys, false, sizeof(bool) * MAX_KEYS);
}
