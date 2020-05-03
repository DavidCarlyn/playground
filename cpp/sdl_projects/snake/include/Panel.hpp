#pragma once

#include <ScreenComponent.hpp>
#include <list>

class Panel : public ScreenComponent {
    public:
        Panel();
        ~Panel();

        Panel( Vector2D<int> size );
        Panel( Vector2D<int> size, Vector2D<int> position);
        Panel( Vector2D<float> size );

        void setBackgroundColor( SDL_Color color ) { _backgroundColor = color; }

        virtual void addComponent( ScreenComponent* component );
        virtual void render( SDL_Renderer* renderer ) override;

    protected:
        std::list<ScreenComponent*> _components;
        SDL_Color _backgroundColor;
};