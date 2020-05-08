#pragma once

#include <Window.hpp>

class ActionListener {
    public:
        ActionListener() {}

        virtual void onAction() {}
};

class Button : public ScreenComponent, public MouseListener {
    public:
        Button() {};
        Button( Vector2D<int> size, Vector2D<int> position = Vector2D<int>( 0, 0 ) ) : ScreenComponent( size, position ) {}
        Button( Vector2D<float> size, Vector2D<float> position = Vector2D<float> ( 0.0f, 0.0f ) ) : ScreenComponent( size, position ) {}
        Button( Vector2D<int> size, Vector2D<float> position ) : ScreenComponent( size, position ) {}
        Button( Vector2D<float> size, Vector2D<int> position ) : ScreenComponent( size, position ) {}

        void addActionListener( ActionListener* listener ) { _actionListeners.push_back( listener ); }

        virtual void onMouseUp( Vector2D<int> pos ) override;
        virtual void render( SDL_Renderer* renderer, SDL_Rect* clip = NULL, const double angle = 0 );

    private:
        std::list<ActionListener*> _actionListeners;
};