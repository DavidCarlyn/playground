#pragma once

#include <SDL.h>

class Test {
    public:
        Test(int x) {
            _x = x;
        }
        int getX();

    private:
        int _x;
};