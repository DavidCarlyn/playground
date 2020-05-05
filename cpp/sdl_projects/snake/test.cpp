/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Engine.hpp>
#include <Window.hpp>

int main( int argc, char* args[] ) {
	Window* window = new Window( "Testing", Vector2D<int>( 1080, 720 ) );

	Panel* testPanel = new Panel( Vector2D<float>( 0.8f, 0.8f ) );
	testPanel->setBackgroundColor( { 100, 200, 50, 255} );

	window->addComponent( testPanel );

	window->display();

	return 0;
}