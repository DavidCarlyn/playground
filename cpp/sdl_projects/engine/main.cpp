/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Engine.hpp>
#include <Window.hpp>

class MyMouseListener : public MouseListener {
    public:
        MyMouseListener() : MouseListener() {}

        void onMouseUp( Vector2D<int> pos ) override {
            std::cout << "x: " << pos.getFirst() << ", y: " << pos.getSecond() << std::endl;
        }

        void onMouseDown( Vector2D<int> pos ) override {
            std::cout << "x: " << pos.getFirst() << ", y: " << pos.getSecond() << std::endl;
        }

        void onMouseMove( Vector2D<int> pos ) override {
            std::cout << "x: " << pos.getFirst() << ", y: " << pos.getSecond() << std::endl;
        }
};

class MyKeyListener : public KeyListener {
    public:
        MyKeyListener() : KeyListener() {}

        void onKeyUp( SDL_Keycode key ) override {
            std::cout << key << std::endl;
        }
};

int main( int argc, char* args[] ) {
	Window* window = new Window( "Testing", Vector2D<int>( 1080, 720 ) );
    //window->addMouseListener( new MyMouseListener() );
    window->addKeyListener( new MyKeyListener() );

	window->display();

	return 0;
}