#pragma once

#include "GameObject.h"

class Card : public GameObject
{
private:
	int number;

public:
	Card(const char* shape, const Vector2& pos, const Dimension& dim, bool visible, int number) : GameObject(shape, pos, dim, visible), number(number)
	{}

	Card(const Card& source): GameObject(source.getShape(), source.getPosition(), source.getDimension(), true), number(source.getNumber())
	{}

	int getNumber() const { return this->number; }
	void setNumber(const int num, const char* shape) {
		this->number = num;
		this->setShape(shape);
	}

	void setNumber(const Card* other) {
		this->number = other->getNumber();
		this->setShape(other->getShape());
	}

	void update(InputManager& input, GameManager& gameManager) override;

	~Card() {}

	static GameObject* GetCardObject(Position paramPosition);
	static GameObject* GetCardObject(Vector2 paramPosition);
	static int GetCardNumber(Position paramPosition);
	static int GetCardNumber(Vector2 paramPosition);
	static int GetCardNumber(GameObject* obj);
	static void swapCard(GameObject* destination, GameObject* source);

};

