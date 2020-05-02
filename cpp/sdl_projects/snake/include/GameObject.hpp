#pragma once

#include <SDL.h>

class GameObject {
    public:
        GameObject();
        GameObject(int x, int y);

        int getX() { return _x; }
        int getY() { return _y; }
        
        void setPos(int x, int y) { _x = x; _y = y; }

        virtual void render(SDL_Renderer* renderer) = 0;
    protected:
        int _x;
        int _y;
};