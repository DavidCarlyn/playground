#pragma once

#include <GameObject.hpp>

class Food : public GameObject {
    public:
        Food();
        Food( int x, int y );
        Food( int x, int y, int w, int h );

        int getWidth() { return _width; }
        int getHeight() { return _height; }
        void setSize( int w, int h ) { _width = w; _height = h; }

        virtual void render( SDL_Renderer* renderer );
        void render( SDL_Renderer* renderer, int xMargin, int yMargin );
    private:
        int _width;
        int _height;
};