/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Engine.hpp>
#include <Window.hpp>
#include <Button.hpp>

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

class MyActionListener : public ActionListener {
    public:
        MyActionListener() {}

        void onAction() override {
            std::cout << "Action" << std::endl;
        }
};

class Scene2 : public Scene {
    public:
        Scene2() : Scene() { _block = NULL; }

        bool build( Panel* p, SDL_Renderer* r ) override;
        bool loop() override;
    private:
        Panel* _block;
};

class Scene1 : public Scene {
    public:
        Scene1() : Scene() { _block = NULL; }

        bool build( Panel* p, SDL_Renderer* r ) override;
        bool loop() override;
        Scene* getNextScene() override { return new Scene2(); }
    private:
        Panel* _block;
};

bool Scene1::build( Panel* windowPanel, SDL_Renderer* renderer ) {
    windowPanel->setDisplayMode( new Relative() );
    _block = new Panel( Vector2D<int>( 50, 50 ) );
    _block->setBackgroundColor( { 100, 255, 0, 255 } );

    windowPanel->addComponent( _block );

    return true;
}

bool Scene1::loop() {
    _block->setPosition( Vector2D<int>( 1, 1 ) + _block->getAbsolutePosition() );

    if ( _block->getAbsolutePosition().getFirst() > 200 ) {
        return false;
    }
    
    return true;
}

bool Scene2::build( Panel* windowPanel, SDL_Renderer* renderer ) {
    windowPanel->setDisplayMode( new Relative() );
    _block = new Panel( Vector2D<int>( 50, 50 ) );
    _block->setBackgroundColor( { 255, 100, 0, 255 } );

    windowPanel->addComponent( _block );

    return true;
}

bool Scene2::loop() {
    _block->setPosition( Vector2D<int>( 1, 1 ) + _block->getAbsolutePosition() );
    if ( _block->getAbsolutePosition().getFirst() > 200 ) {
        return false;
    }
    
    return true;
}

int main( int argc, char* args[] ) {
	Window* window = new Window( "Testing", Vector2D<int>( 1080, 720 ) );
    window->setScene( new Scene1() );

	window->display();

	return 0;
}