#include <Snake.hpp>

Snake::Snake() : ScreenComponent() {
    _direction = Direction::DOWN;
    _gamePosition = Vector2D<int>( 0, 0 );
    _body = new SnakePart( _absoluteSize,  Vector2D<int>( _gamePosition.getFirst(), _gamePosition.getSecond() - 1 ) );
    _body->setPosition( _absolutePosition );
}

Snake::Snake( Vector2D<int> size, Vector2D<int> gamePosition ) : ScreenComponent( size ) {
    _direction = Direction::DOWN;
    _gamePosition = gamePosition;
    _body = new SnakePart( size, Vector2D<int>( gamePosition.getFirst(), gamePosition.getSecond() - 1 ) );
    _body->setPosition( _absolutePosition );
}

void Snake::setSize( Vector2D<int> size ) {
    ScreenComponent::setSize( size );
    _body->setSize( size );
}

void Snake::setPosition( Vector2D<int> position ) {
    ScreenComponent::setPosition( position );
    _body->setPosition( position );
}

void Snake::handleInput( SDL_Event e ) {
	if ( (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.repeat == 0 ) {
        switch( e.key.keysym.sym ) {
            case SDLK_UP:
            case SDLK_w:
                if ( _direction == Direction::DOWN ) break;
                _direction = Direction::UP;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                if ( _direction == Direction::UP ) break;
                _direction = Direction::DOWN;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                if ( _direction == Direction::RIGHT ) break;
                _direction = Direction::LEFT;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                if ( _direction == Direction::LEFT ) break;
                _direction = Direction::RIGHT;
                break;
        }
    }
}

bool Snake::didCollide( Vector2D<int> gamePosition ) {
    if ( _gamePosition.equals( gamePosition ) ) return true;
    return didCollideWithBody( gamePosition );
}

bool Snake::didCollideWithBody( Vector2D<int> gamePosition ) {
    return _body->didCollide( gamePosition );
}

void Snake::move() {
    _body->update( _gamePosition );
    int x = _gamePosition.getFirst();
    int y = _gamePosition.getSecond();
    switch(_direction) {
        case UP:
            y -= 1;
            break;
        case RIGHT:
            x += 1;
            break;
        case DOWN:
            y += 1;
            break;
        case LEFT:
            x -= 1;
            break;
        default:
            break;
    }

    _gamePosition = Vector2D<int>( x, y );
}

void Snake::grow() {
    _body->grow( _gamePosition );
}

void Snake::render( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
    SDL_Rect rect;
    rect.x = getRenderPosition().getFirst() + _gamePosition.getFirst() * getRenderSize().getFirst();
    rect.y = getRenderPosition().getSecond() + _gamePosition.getSecond() * getRenderSize().getSecond();
    rect.w = getRenderSize().getFirst();
    rect.h = getRenderSize().getSecond();
    SDL_RenderFillRect( renderer, &rect );
    _body->updateAbsolutePosition( getRenderPosition() );
    _body->render( renderer );

}

Snake::SnakePart::SnakePart() : ScreenComponent() {
    _next = NULL;
    _gamePosition = Vector2D<int>( 0, 0 );
}

Snake::SnakePart::SnakePart( Vector2D<int> size, Vector2D<int> gamePosition ) : ScreenComponent( size ) {
    _next = NULL;
    _gamePosition = gamePosition;
}

void Snake::SnakePart::setSize( Vector2D<int> size ) {
    ScreenComponent::setSize( size );
    if ( _next != NULL ) {
        _next->setSize( size );
    }
}

void Snake::SnakePart::setPosition( Vector2D<int> position ) {
    ScreenComponent::setPosition( position );
    if ( _next != NULL ) {
        _next->setPosition( position );
    }
}

bool Snake::SnakePart::didCollide( Vector2D<int> gamePosition ) {
    if ( _gamePosition.equals( gamePosition ) ) return true;
    if ( _next == NULL ) return false;
    return _next->didCollide( gamePosition );
}

void Snake::SnakePart::update( Vector2D<int> gamePosition ) {
    if ( _next != NULL ) {
        _next->update( _gamePosition );
    }

    _gamePosition = gamePosition;
}

void Snake::SnakePart::grow( Vector2D<int> prevGamePosition ) {
    if ( _next != NULL ) {
        _next->grow( _gamePosition );
        return;
    }

    int dx = 0;
    int dy = 0;

    if ( _gamePosition.getFirst() != prevGamePosition.getFirst() ) {
        dx = _gamePosition.getFirst() - prevGamePosition.getFirst();
    } else {
        dy = _gamePosition.getSecond() - prevGamePosition.getSecond();
    }

    _next = new SnakePart( _absoluteSize, Vector2D<int>( _gamePosition.getFirst() + dx, _gamePosition.getSecond() + dy ) ); //TODO: set correct position
    _next->setPosition( _absolutePosition );
}

void Snake::SnakePart::updateAbsolutePosition( Vector2D<int> position ) {
    setAbsolutePosition( position );
    if ( _next != NULL ) {
        _next->setAbsolutePosition( position );
    }
}

void Snake::SnakePart::render( SDL_Renderer* renderer ) {
    SDL_Rect rect;
    rect.x = getAbsolutePosition().getFirst() + _gamePosition.getFirst() * getAbsoluteSize().getFirst();
    rect.y = getAbsolutePosition().getSecond() + _gamePosition.getSecond() * getAbsoluteSize().getSecond();
    rect.w = getAbsoluteSize().getFirst();
    rect.h = getAbsoluteSize().getSecond();
    SDL_RenderFillRect( renderer, &rect );
    if ( _next != NULL ) {
        _next->render( renderer );
    }
}