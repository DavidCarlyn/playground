#pragma once

#include <Panel.hpp>
#include <string>

class Window {
    public:
        Window();
        Window( std::string name );
        Window( Vector2D<int> size );
        Window( std::string name, Vector2D<int> size );
        ~Window();

        Panel* getPanel() { return _windowPanel; }
        SDL_Renderer* getRenderer() { return _renderer; }

        void addComponent( ScreenComponent* component ) { _windowPanel->addComponent( component ); }
        void display();

    protected:
        SDL_Renderer* _renderer;

    private:
        Panel* _windowPanel;
        SDL_Window* _window;
        SDL_Surface* _surface;
        Vector2D<int> _size;

};