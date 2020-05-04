#include <Food.hpp>

Food::Food() : ScreenComponent() {
    _gamePosition = Vector2D<int>( 0, 0 );
}

Food::Food( Vector2D<int> size, Vector2D<int> position ) : ScreenComponent( size ) {
    _gamePosition = position;
}

void Food::render( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_Rect rect;
    rect.x = _position.getFirst() + _gamePosition.getFirst() * _size.getFirst();
    rect.y = _position.getSecond() + _gamePosition.getSecond() * _size.getSecond();
    rect.w = _size.getFirst();
    rect.h = _size.getSecond();
    SDL_RenderFillRect( renderer, &rect );
}
