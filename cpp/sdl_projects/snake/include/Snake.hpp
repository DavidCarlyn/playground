#pragma once

#include <ScreenComponent.hpp>

class Snake : public ScreenComponent {
    public:
        Snake();
        Snake( Vector2D<int> size, Vector2D<int> gamePosition );

        void setSize( Vector2D<int> size );
        void setPosition( Vector2D<int> position ) override;
        Vector2D<int> getGamePosition() { return _gamePosition; }

        void handleInput( SDL_Event e );
        bool didCollide( Vector2D<int> gamePosition );
        bool didCollideWithBody( Vector2D<int> gamePosition );

        void move();
        void grow();

        virtual void render( SDL_Renderer* renderer ) override;
    private:
        class SnakePart : public ScreenComponent {
            public:
                SnakePart();
                SnakePart( Vector2D<int> size, Vector2D<int> gamePosition );

                void setAbsolutePosition( Vector2D<int> position ) { ScreenComponent::setPosition( position ); }
                void setSize( Vector2D<int> size );
                void setPosition( Vector2D<int> position ) override;
                Vector2D<int> getGamePosition() { return _gamePosition; }

                bool didCollide( Vector2D<int> gamePosition );

                void update( Vector2D<int> gamePosition );
                void grow( Vector2D<int> prevGamePosition );

                void updateAbsolutePosition( Vector2D<int> position );

                virtual void render( SDL_Renderer* renderer ) override;
            private:
                SnakePart* _next;
                Vector2D<int> _gamePosition;
        };

        enum Direction {
            UP,
            RIGHT,
            DOWN,
            LEFT
        };

        Direction _direction;
        SnakePart* _body;
        Vector2D<int> _gamePosition;

};