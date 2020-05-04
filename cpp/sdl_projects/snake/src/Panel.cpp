#include <Panel.hpp>

Panel::Panel() : ScreenComponent( Vector2D<float>( 1.0f, 1.0f ) ) {
    _backgroundColor = { 255, 255, 255, 255 };
}

Panel::Panel( Vector2D<int> size ) : ScreenComponent( size ) {
    _backgroundColor = { 255, 255, 255, 255 };
}

Panel::Panel( Vector2D<int> size, Vector2D<int> position) : ScreenComponent( size, position ) {
    _backgroundColor = { 255, 255, 255, 255 };
}

Panel::Panel( Vector2D<float> size ) : ScreenComponent( size ) {
    _backgroundColor = { 255, 255, 255, 255 };
}

void Panel::setSize( Vector2D<int> size ) {
    _size = size;

    std::list<ScreenComponent*> listCopy = _components;
    _components.clear();

    for ( auto comp : listCopy ) {
        addComponent( comp );
    }
}

void Panel::setSize( Vector2D<float> size ) {
    _relativeSize = size;
    float xScale = size.getFirst() / _relativeSize.getFirst();
    float yScale = size.getSecond() / _relativeSize.getSecond();

    setSize( Vector2D<int>( xScale * _size.getFirst(), yScale * _size.getSecond() ) );
}


Panel::~Panel() {
    while ( _components.size() > 0 ) {
        delete _components.front();
        _components.pop_front();
    }
}

//TODO: decide whether to adjust coordinates at component adding or during render
//TODO: decide what to do when size goes off screen/panel
//TODO: prepare to change this a lot

void Panel::addComponent( ScreenComponent* component ) {

    switch( component->getDisplayType() ) {
        case ABSOLUTE: {
            Vector2D<int> pos = component->getPosition();
            component->setPosition( Vector2D<int>( pos.getFirst() + _position.getFirst(), pos.getSecond() + _position.getSecond() ) );
            }
            break;
        case RELATIVE: {
            int panelXEnd = _position.getFirst() + _size.getFirst();
            int maxHeight = 0;
            ScreenComponent* lastRelComp = NULL;
            for ( auto comp : _components ) {
                if ( comp->getDisplayType() == RELATIVE ) {
                    int bottomHeight = comp->getPosition().getSecond() + comp->getSize().getSecond();
                    if ( bottomHeight >  maxHeight ) {
                        maxHeight = bottomHeight;
                    }
                    lastRelComp = comp;
                }
            }

            Vector2D<int> desiredSize = Vector2D<int>(
                component->getRelativeSize().getFirst() * _size.getFirst(),
                component->getRelativeSize().getSecond() * _size.getSecond()
            );
            component->setSize( desiredSize );
            if ( lastRelComp == NULL ) {
                component->setPosition( _position );
            } else if (panelXEnd - lastRelComp->getPosition().getFirst() - lastRelComp->getSize().getFirst() > desiredSize.getFirst()) {
                component->setPosition( Vector2D<int>(
                    lastRelComp->getPosition().getFirst() + lastRelComp->getSize().getFirst(),
                    lastRelComp->getPosition().getSecond()
                ) );
            } else {
                component->setPosition( Vector2D<int>(
                    _position.getFirst(),
                    maxHeight
                ) );
            }

            }

            break;
        default:
            break;
    }

    _components.push_back( component );
}

void Panel::render( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a );
    SDL_Rect rect;
    rect.x = _position.getFirst();
    rect.y = _position.getSecond();
    rect.w = _size.getFirst();
    rect.h = _size.getSecond();
    SDL_RenderFillRect( renderer, &rect );

    for ( auto comp : _components ) {
        comp->render( renderer );
    }
}