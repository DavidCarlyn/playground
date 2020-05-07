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
    rect.x = getRenderPosition().getFirst() + _gamePosition.getFirst() * getRenderSize().getFirst();
    rect.y = getRenderPosition().getSecond() + _gamePosition.getSecond() * getRenderSize().getSecond();
    rect.w = getRenderSize().getFirst();
    rect.h = getRenderSize().getSecond();
    SDL_RenderFillRect( renderer, &rect );
}
