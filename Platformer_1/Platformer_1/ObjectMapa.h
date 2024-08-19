#pragma once
#include <SFML/Graphics.hpp>
#include "OwnGCF.h"
#include "ParametrsGame.h"
using namespace sf;

 
enum class Type{Empty, Block, Slope};

class Object {
protected:
	Type tp;
public:
	Object(Type tp) :tp{ tp } {}

	~Object() {}
};

class Block : public Object {
protected:
	RectangleShape shape = InitialRectangleShape(Vector2f(Pr::sz, Pr::sz), Color(255, 255, 255), Vector2f(0, 0));
public:
	Block():Object{Type::Block} {}
	Block(Color col) :Object{ Type::Block } {
		shape.setFillColor(col);
	}
	Block(Color col, Texture* texture) :Object{ Type::Block } {
		shape.setFillColor(col);
		shape.setTexture(texture);
	}
	void setTexture(Texture* texture) {
		shape.setTexture(texture);
	}
	void setPosition(Vector2f pos) {
		shape.setPosition(pos);
	}
	void setFillColor(Color col) {
		shape.setFillColor(col);
	}
	Color getFillColor() {
		return shape.getFillColor();
	}
	RectangleShape getShape() {
		return shape;
	}
	~Block() {}
};
