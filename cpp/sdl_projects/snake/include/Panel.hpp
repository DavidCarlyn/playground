#pragma once

#include <ScreenComponent.hpp>
#include <DisplayMode.hpp>
#include <list>

class Panel : public ScreenComponent {
    public:
        Panel();
        ~Panel();

        Panel( Vector2D<int> size, Vector2D<int> position = Vector2D<int>( 0, 0 ), DisplayMode* displayMode = new Relative() );
        Panel( Vector2D<float> size, Vector2D<float> position = Vector2D<float>( 0.0f, 0.0f ), DisplayMode* displayMode = new Relative() );
        Panel( Vector2D<int> size, Vector2D<float> position, DisplayMode* displayMode = new Relative() );
        Panel( Vector2D<float> size, Vector2D<int> position, DisplayMode* displayMode = new Relative() );

        void setBackgroundColor( SDL_Color color ) { _backgroundColor = color; }

        virtual void addComponent( ScreenComponent* component );
        virtual void render( SDL_Renderer* renderer, SDL_Rect* clip = NULL, const double angle = 0 ) override;

    protected:
        std::list<ScreenComponent*> _components;
        SDL_Color _backgroundColor;
        DisplayMode* _displayMode;
};