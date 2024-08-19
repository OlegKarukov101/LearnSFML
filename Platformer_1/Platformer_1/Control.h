#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Control {
protected: 
public:
	virtual void moveLeft() = 0;
	virtual void moveRight() = 0;
	virtual void moveJump() = 0;
	virtual void Action() = 0;
};

class ControlComputer : public  Control{

public:
	void CheckPress() {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            //if(hero.isGround_()) 
            moveLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            //if(hero.isGround_()) 
            moveRight();
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            //if (hero.isGround_())
            moveJump();
        }
	}
};
