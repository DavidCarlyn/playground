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

	Panel* testPanel = new Panel( Vector2D<float>( 1.0f, 1.0f ), Vector2D<int>( 0, 0 ), new Grid( 3, 3 ) );
	testPanel->setBackgroundColor( { 100, 200, 50, 255} );

	window->addComponent( testPanel );

	Panel* grid1 = new Panel( Vector2D<float>( 1.0f, 1.0f ) );
	grid1->setBackgroundColor( { 255, 0, 0, 255} );
	Panel* grid2 = new Panel( Vector2D<float>( 1.0f, 1.0f ) );
	grid2->setBackgroundColor( { 0, 255, 0, 255} );
	Panel* grid3 = new Panel( Vector2D<float>( 1.0f, 1.0f ) );
	grid3->setBackgroundColor( { 0, 0, 255, 255} );
	Panel* grid4 = new Panel( Vector2D<float>( 1.0f, 1.0f ) );
	grid4->setBackgroundColor( { 255, 0, 255, 255} );

	testPanel->addComponent( grid1 );
	testPanel->addComponent( grid2 );
	testPanel->addComponent( grid3 );
	testPanel->addComponent( grid4 );


	window->display();

	return 0;
}