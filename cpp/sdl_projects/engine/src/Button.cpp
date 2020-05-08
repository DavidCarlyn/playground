#include <Button.hpp>

#include <iostream>
void Button::onMouseUp( Vector2D<int> pos ) {
    if ( pos.getFirst() < getRenderPosition().getFirst() ) { return; }
    if ( pos.getFirst() > getRenderPosition().getFirst() + getRenderSize().getFirst() ) { return; }
    if ( pos.getSecond() < getRenderPosition().getSecond() ) { return; }
    if ( pos.getSecond() > getRenderPosition().getSecond() + getRenderSize().getSecond() ) { return; }

    for ( auto l : _actionListeners ) {
        l->onAction();
    }
}

void Button::render( SDL_Renderer* renderer, SDL_Rect* clip, const double angle ) {
    SDL_Rect rect;
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0xFF, 0xFF );
    rect.x = getRenderPosition().getFirst();
    rect.y = getRenderPosition().getSecond();
    rect.w = getRenderSize().getFirst();
    rect.h = getRenderSize().getSecond();

    SDL_RenderFillRect( renderer, &rect );
}