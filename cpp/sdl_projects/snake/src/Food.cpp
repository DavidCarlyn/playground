#include <Food.hpp>

Food::Food() : GameObject() {
    _width = 16;
    _height = 16;
}

Food::Food( int x, int y ) : GameObject( x, y ) {
    _width = 16;
    _height = 16;
}

Food::Food( int x, int y, int w, int h ) : GameObject( x, y ) {
    _width = w;
    _height = h;
}

void Food::render( SDL_Renderer* renderer ) {
    render( renderer, 0, 0 );
}

void Food::render( SDL_Renderer* renderer, int xMargin, int yMargin ) {
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_Rect rect;
    rect.x = xMargin + _x * _width;
    rect.y = yMargin + _y * _height;
    rect.w = _width;
    rect.h = _height;
    SDL_RenderFillRect( renderer, &rect );
}
