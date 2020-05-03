#include <Window.hpp>
#include <iostream>

Window::Window() : Window( "NO NAME" ) {}

Window::Window( std::string name ) : Window( name, Vector2D<int> ( 1080, 720 ) ) {}

Window::Window( Vector2D<int> size ) Window( "NO NAME", size ) {}

Window::Window( std::string name, Vector2D<int> size ) {
    _size = size;
	_window = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.getFirst(), size.getSecond(), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if ( _window == NULL ) {
		std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}

    _surface = SDL_GetWindowSurface( _window );

    _renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( _renderer == NULL ) {
		std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}
}

Window::~Window() {
    SDL_FreeSurface( _surface );
    SDL_DestroyRenderer( _renderer );
    SDL_DestroyWindow( _window );

    _surface = NULL;
    _window = NULL;
    _renderer = NULL;
}

void Window::display() {

}
