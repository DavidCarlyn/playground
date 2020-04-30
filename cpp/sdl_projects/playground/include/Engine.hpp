#pragma once

#include <SDL.h>
#include <string>

class Engine {
    public:
        Engine();

        SDL_Window* createWindow();
        SDL_Surface* createSurface(SDL_Window*);
        SDL_Surface* createImageSurface(SDL_Surface*, std::string);

        void freeSurface(SDL_Surface*);
        void destroyWindow(SDL_Window*);
        void close();
    private:
        const int _screenWidth = 640;
        const int _screenHeight = 480;
};