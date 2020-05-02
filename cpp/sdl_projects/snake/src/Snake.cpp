#include <Snake.hpp>

Snake::Snake() : GameObject() {
    _direction = Direction::DOWN;
    _width = 16;
    _height = 16;
    _body = new SnakePart(_x, _y - 1, _width, _height);
}

Snake::Snake(int x, int y) : GameObject(x, y) {
    _direction = Direction::DOWN;
    _width = 16;
    _height = 16;
    _body = new SnakePart(_x, _y - 1, _width, _height);
}

Snake::Snake(int x, int y, int w, int h) : GameObject(x, y) {
    _direction = Direction::DOWN;
    _width = w;
    _height = h;
    _body = new SnakePart(_x, _y - 1, _width, _height);
}

void Snake::setSize(int w, int h) {
    _width = w;
    _height = h;

    _body->setSize(w, h);
}

void Snake::handleInput( SDL_Event e ) {
	if ( (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.repeat == 0 ) {
        switch( e.key.keysym.sym ) {
            case SDLK_UP:
                if ( _direction == Direction::DOWN ) break;
                _direction = Direction::UP;
                break;
            case SDLK_DOWN:
                if ( _direction == Direction::UP ) break;
                _direction = Direction::DOWN;
                break;
            case SDLK_LEFT:
                if ( _direction == Direction::RIGHT ) break;
                _direction = Direction::LEFT;
                break;
            case SDLK_RIGHT:
                if ( _direction == Direction::LEFT ) break;
                _direction = Direction::RIGHT;
                break;
        }
    }
}

bool Snake::didCollide(int x, int y) {
    if ( _x == x && _y == y ) return true;
    return didCollideWithBody(x, y);
}

bool Snake::didCollideWithBody(int x, int y) {
    return _body->didCollide(x, y);
}

void Snake::move() {
    _body->update(_x, _y);
    switch(_direction) {
        case UP:
            _y -= 1;
            break;
        case RIGHT:
            _x += 1;
            break;
        case DOWN:
            _y += 1;
            break;
        case LEFT:
            _x -= 1;
            break;
        default:
            break;
    }
}

void Snake::grow() {
    _body->grow( _x, _y );
}

void Snake::render(SDL_Renderer* renderer) {
    render( renderer, 0, 0 );
}

void Snake::render(SDL_Renderer* renderer, int xMargin, int yMargin ) {
    SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
    SDL_Rect rect;
    rect.x = xMargin + _x * _width;
    rect.y = yMargin + _y * _height;
    rect.w = _width;
    rect.h = _height;
    SDL_RenderFillRect( renderer, &rect );
    _body->render( renderer, xMargin, yMargin );

}

Snake::SnakePart::SnakePart() : GameObject() {
    _next = NULL;
    _width = 16;
    _height = 16;
}

Snake::SnakePart::SnakePart(int x, int y) : GameObject(x, y) {
    _next = NULL;
    _width = 16;
    _height = 16;
}

Snake::SnakePart::SnakePart(int x, int y, int w, int h) : GameObject(x, y) {
    _next = NULL;
    _width = w;
    _height = h;
}

void Snake::SnakePart::setSize(int w, int h) {
    _width = w;
    _height = h;
    if ( _next != NULL ) {
        _next->setSize(w, h);
    }
}

bool Snake::SnakePart::didCollide(int x, int y) {
    if ( _x == x && _y == y ) return true;

    if ( _next == NULL ) return false;

    return _next->didCollide(x, y);
}

void Snake::SnakePart::update(int x, int y) {
    if ( _next != NULL ) {
        _next->update(_x, _y);
    }
    _x = x;
    _y = y;
}

void Snake::SnakePart::grow( int prevX, int prevY ) {
    if ( _next != NULL ) {
        _next->grow( _x, _y );
        return;
    }

    int dx = 0;
    int dy = 0;

    if ( _x != prevX ) {
        dx = _x - prevX;
    } else {
        dy = _y - prevY;
    }

    _next = new SnakePart( _x + dx, _y + dy, _width, _height ); //TODO: set correct position
}

void Snake::SnakePart::render( SDL_Renderer* renderer ) {
    render( renderer, 0, 0 );
}

void Snake::SnakePart::render( SDL_Renderer* renderer, int xMargin, int yMargin ) {
    SDL_Rect rect;
    rect.x = xMargin + _x * _width;
    rect.y = yMargin + _y * _height;
    rect.w = _width;
    rect.h = _height;
    SDL_RenderFillRect( renderer, &rect );
    if ( _next != NULL ) {
        _next->render( renderer, xMargin, yMargin );
    }
}