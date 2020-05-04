#pragma once

#include <SDL.h>

template <class T>
class Vector2D {
    public:
        Vector2D() : _v0( 0 ), _v1( 0 ) {}
        Vector2D( T v0, T v1 ) : _v0( v0 ), _v1( v1 ) {}
        T getFirst() { return _v0; }
        T getSecond() { return _v1; }
        void setFirst( T v ) { _v0 = v; }
        void setSecond( T v ) { _v1 = v; }

        bool equals( Vector2D rhs ) { return rhs.getFirst() == _v0 && rhs.getSecond() == _v1; }

    private:
        T _v0;
        T _v1;
};

enum DisplayType {
    RELATIVE,
    ABSOLUTE
};

class ScreenComponent {
    public:
        ScreenComponent();
        ScreenComponent( Vector2D<int> size );
        ScreenComponent( Vector2D<int> size, Vector2D<int> position );
        ScreenComponent( Vector2D<float> size );

        void setDisplayType( DisplayType type ) { _displayType = type; }
        virtual void setPosition( Vector2D<int> position ) { _position = position; }
        virtual void setSize( Vector2D<int> size ) { _size = size; }
        virtual void setSize( Vector2D<float> size ) { _relativeSize = size; }

        DisplayType getDisplayType() { return _displayType; }
        Vector2D<int> getPosition() { return _position; }
        Vector2D<int> getSize() { return _size; }
        Vector2D<float> getRelativeSize() { return _relativeSize; }

        virtual void render( SDL_Renderer* renderer ) = 0;

    protected:
        DisplayType _displayType;
        Vector2D<int> _position;
        Vector2D<int> _size;
        Vector2D<float> _relativeSize;
        //TODO: margins and paddings
};