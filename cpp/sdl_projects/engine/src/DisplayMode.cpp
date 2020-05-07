#include <DisplayMode.hpp>
#include <stdio.h>

//TODO: decide whether to adjust coordinates at component adding or during render
//TODO: decide what to do when size goes off screen/panel

//TODO: [BUG] on relative positioning and sizing. pixel off when 100%
void Relative::positionComponents( SDL_Rect* clippingRectangle, std::list<ScreenComponent*> components ) {
    int x = clippingRectangle->x;
    int y = clippingRectangle->y;
    int w = clippingRectangle->w;
    int h = clippingRectangle->h;

    int nextX = 0;
    int currY = 0;
    int nextY = 0;
    for ( auto comp : components ) {
        if ( comp->getSizeConstraint() == ABSOLUTE ) {
            comp->setRenderSize( comp->getAbsoluteSize() );
        } else {
            Vector2D<int> newSize( Vector2D<int>( comp->getRelativeSize() * Vector2D<float>( w, h ) ) );
            //printf("Width: %d | Height: %d || ", newPos.getFirst(), newPos.getSecond() );
            comp->setRenderSize( newSize );
        }

        if ( comp->getPositionConstraint() == ABSOLUTE ) {
            comp->setRenderPosition( comp->getAbsolutePosition() + Vector2D<int>( x, y ) );
        } else {
            int compWidth = comp->getRenderSize().getFirst();
            int compHeight = comp->getRenderSize().getSecond();
            if ( compHeight > nextY ) { nextY = compHeight; }
            if ( compWidth > w - nextX ) {
                currY = nextY;
                nextY += compHeight;
                nextX = compWidth;
                comp->setRenderPosition( Vector2D<int>( 0, currY ) + Vector2D<int>( x, y ) );            
            } else {
                comp->setRenderPosition( Vector2D<int>( nextX, currY ) + Vector2D<int>( x, y ) );
                nextX += compWidth;
            }
        }
    }
}

void Anchor::positionComponents( SDL_Rect* clippingRectangle, std::list<ScreenComponent*> components ) {

}

//TODO: [BUG] not full size when not evenly divisible
void Grid::positionComponents( SDL_Rect* clippingRectangle, std::list<ScreenComponent*> components ) {
    int x = clippingRectangle->x;
    int y = clippingRectangle->y;
    int w = clippingRectangle->w;
    int h = clippingRectangle->h;
    //TODO: may have to give some blocks a pixel more if uneven
    Vector2D<int> blockSize( w / _cols, h / _rows );
    //printf("X: %d, Y: %d || ", blockSize.getFirst(), blockSize.getSecond() );
    int i = 0;
    for ( auto comp : components ) {
        comp->setRenderSize( blockSize );
        comp->setRenderPosition( Vector2D<int>( x, y ) + Vector2D<int>( Vector2D<int>( i%_cols, i/_rows ) * blockSize ) );
        ++i;
    }
}