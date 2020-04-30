#include <Dot.hpp>

Dot::Dot(Texture* dotTexture) {
    _x = 0;
    _y = 0;

    _xVel = 0;
    _yVel = 0;

    _texture = dotTexture;
}

Dot::~Dot() {
    delete _texture;
}

void Dot::handleEvent( SDL_Event& e ) {
    //If a key was pressed
	if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: _yVel -= DOT_VEL; break;
            case SDLK_DOWN: _yVel += DOT_VEL; break;
            case SDLK_LEFT: _xVel -= DOT_VEL; break;
            case SDLK_RIGHT: _xVel += DOT_VEL; break;
        }
    } else if ( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
        //Adjust the velocity
        switch ( e.key.keysym.sym ) {
            case SDLK_UP: _yVel += DOT_VEL; break;
            case SDLK_DOWN: _yVel -= DOT_VEL; break;
            case SDLK_LEFT: _xVel += DOT_VEL; break;
            case SDLK_RIGHT: _xVel -= DOT_VEL; break;
        }
    }
}

void Dot::move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT) {
    //Move the dot left or right
    _x += _xVel;

    //If the dot went too far to the left or right
    if( ( _x < 0 ) || ( _x + DOT_WIDTH > SCREEN_WIDTH ) ) {
        //Move back
        _x -= _xVel;
    }

    //Move the dot up or down
    _y += _yVel;

    //If the dot went too far up or down
    if( ( _y < 0 ) || ( _y + DOT_HEIGHT > SCREEN_HEIGHT ) ) {
        //Move back
        _y -= _yVel;
    }
}

void Dot::render(SDL_Renderer* renderer) {
    //Show the dot
	_texture->render( renderer, _x, _y );
}