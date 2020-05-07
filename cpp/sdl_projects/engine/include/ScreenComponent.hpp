#pragma once

#include <SDL.h>

template <class T>
class Vector2D {
    public:
        Vector2D() : _v0( 0 ), _v1( 0 ) {}
        template<class K>
        Vector2D( const Vector2D<K> &vector ) : _v0( vector.getFirst() ), _v1( vector.getSecond() ) {}
        Vector2D( T v0, T v1 ) : _v0( v0 ), _v1( v1 ) {}
        T getFirst() const { return _v0; }
        T getSecond() const { return _v1; }
        void setFirst( T v ) { _v0 = v; }
        void setSecond( T v ) { _v1 = v; }

        Vector2D<T> operator+( const Vector2D<T>& rhs ) {
            return Vector2D<T>( _v0 + rhs._v0, _v1 + rhs._v1 );
        }

        Vector2D<T> operator*( const Vector2D<T>& rhs ) {
            return Vector2D<T>( _v0 * rhs._v0, _v1 * rhs._v1 );
        }

        bool equals( Vector2D rhs ) { return rhs.getFirst() == _v0 && rhs.getSecond() == _v1; }


    private:
        T _v0;
        T _v1;
};

//TODO: set positioning and size to have an independent display type
enum DisplayConstraint {
    RELATIVE,
    ABSOLUTE
};

//TODO: by default all screen components should be NONE. Have ability to set anchor location
enum AnchorLocation {
    NONE,
    NORTHWEST,  NORTH,  NORTHEAST,
    WEST,       CENTER, EAST,
    SOUTHWEST,  SOUTH,  SOUTHEAST
};

class ScreenComponent {
    public:
        ScreenComponent();
        ScreenComponent( Vector2D<int> size, Vector2D<int> position = Vector2D<int>( 0, 0 ) );
        ScreenComponent( Vector2D<float> size, Vector2D<float> position = Vector2D<float> ( 0.0f, 0.0f ) );
        ScreenComponent( Vector2D<int> size, Vector2D<float> position );
        ScreenComponent( Vector2D<float> size, Vector2D<int> position );

        virtual void setPositionConstraint( DisplayConstraint constraint ) { _positionConstraint = constraint; }
        virtual void setSizeConstraint( DisplayConstraint constraint ) { _sizeConstraint = constraint; }
        virtual void setPosition( Vector2D<int> position ) { _absolutePosition = position; }
        virtual void setPosition( Vector2D<float> position ) { _relativePosition = position; }
        virtual void setSize( Vector2D<int> size ) { _absoluteSize = size; }
        virtual void setSize( Vector2D<float> size ) { _relativeSize = size; }

        void setAnchorLocation( AnchorLocation anchor ) { _anchor = anchor; }
        AnchorLocation getAnchorLocation() { return _anchor; }

        void setRenderPosition( Vector2D<int> position ) { _renderPosition = position; }
        void setRenderSize( Vector2D<int> size ) { _renderSize = size; }

        DisplayConstraint getPositionConstraint() const { return _positionConstraint; }
        DisplayConstraint getSizeConstraint() const { return _sizeConstraint; }

        Vector2D<int> getAbsolutePosition() const { return _absolutePosition; }
        Vector2D<float> getRelativePosition() const { return _relativePosition; }

        Vector2D<int> getAbsoluteSize() const { return _absoluteSize; }
        Vector2D<float> getRelativeSize() const { return _relativeSize; }

        Vector2D<int> getRenderPosition() const { return _renderPosition; }
        Vector2D<int> getRenderSize() const { return _renderSize; }

        virtual void render( SDL_Renderer* renderer ) = 0;

    protected:
        AnchorLocation _anchor;
        DisplayConstraint _positionConstraint;
        DisplayConstraint _sizeConstraint;
        Vector2D<int> _absolutePosition;
        Vector2D<int> _absoluteSize;
        Vector2D<float> _relativePosition;
        Vector2D<float> _relativeSize;
        //TODO: margins and paddings
    private:
        Vector2D<int> _renderPosition;
        Vector2D<int> _renderSize;

};