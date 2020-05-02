#pragma once

#include <GameObject.hpp>

class Snake : public GameObject {
    public:
        Snake();
        Snake( int x, int y );
        Snake( int x, int y, int w, int h );

        int getWidth() { return _width; }
        int getHeight() { return _height; }
        void setSize( int w, int h );

        void handleInput( SDL_Event e );
        bool didCollide( int x, int y );
        bool didCollideWithBody( int x, int y );

        void move();
        void grow();

        virtual void render( SDL_Renderer* renderer );
        void render( SDL_Renderer* renderer, int xMargin, int yMargin );
    private:
        class SnakePart : public GameObject {
            public:
                SnakePart();
                SnakePart( int x, int y );
                SnakePart( int x, int y, int w, int h );

                int getWidth() { return _width; }
                int getHeight() { return _height; }
                void setSize( int w, int h );

                bool didCollide( int x, int y );

                void update( int x, int y );
                void grow( int prevX, int prevY );

                virtual void render( SDL_Renderer* renderer );
                void render( SDL_Renderer* renderer, int xMargin, int yMargin );
            private:
                SnakePart* _next;
                int _width;
                int _height;
        };

        enum Direction {
            UP,
            RIGHT,
            DOWN,
            LEFT
        };

        Direction _direction;
        SnakePart* _body;

        int _width;
        int _height;

};