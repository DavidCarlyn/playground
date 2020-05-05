#pragma once

#include<SDL.h>

class Scene {
    public:
        Scene() : _window( NULL ), _surface( NULL ), _renderer( NULL ) {}
        Scene( SDL_Window* w, SDL_Surface* s, SDL_Renderer* r ) : _window( w ), _surface( s ), _renderer( r ) {}

        void setWindow( SDL_Window* w ) { _window = w; }
        void setSurface( SDL_Surface* s ) { _surface = s; }
        void setRenderer( SDL_Renderer* r ) { _renderer = r; }

        virtual int start() = 0;
    protected:
        SDL_Window* _window;
        SDL_Surface* _surface;
        SDL_Renderer* _renderer;
};