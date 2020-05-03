#include <ScreenComponent.hpp>

ScreenComponent::ScreenComponent() {
    _size = Vector2D<int>( 0, 0 );
    _position = Vector2D<int>( 0, 0 );
    _displayType = DisplayType::RELATIVE;
}

ScreenComponent::ScreenComponent( Vector2D<int> size ) {
    _size = size;
    _position = Vector2D<int>( 0, 0 );
    _displayType = DisplayType::ABSOLUTE;
}

ScreenComponent::ScreenComponent( Vector2D<int> size, Vector2D<int> position ) {
    _size = size;
    _position = position;
    _displayType = DisplayType::ABSOLUTE;
}

ScreenComponent::ScreenComponent( Vector2D<float> size ) {
    _relativeSize = size;
    _size = Vector2D<int>( 0, 0 );
    _position = Vector2D<int>( 0, 0 );
    _displayType = DisplayType::RELATIVE;
}