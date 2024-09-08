#include "Card.h"
#include "GameManager.h"
#include "InputManager.h"
#include "GameObject.h"

GameObject* Card::GetCardObject(Position paramPosition) {

	for (int i = 0; i < max_objs; i++) {
		if (objs[i] == nullptr) continue;
		Vector2 pos = objs[i]->getPosition();
		Dimension dim = objs[i]->getDimension();

		if ((pos.x <= paramPosition.x) && ((pos.x + dim.x - 1) >= paramPosition.x)
			&& (pos.y <= paramPosition.y) && ((pos.y + dim.y - 1) >= paramPosition.y))
			return objs[i];
	}
	return nullptr;
}

GameObject* Card::GetCardObject(Vector2 paramPosition) {

	for (int i = 0; i < max_objs; i++) {
		if (objs[i] == nullptr) continue;
		Vector2 pos = objs[i]->getPosition();
		Dimension dim = objs[i]->getDimension();

		if ((pos.x <= paramPosition.x) && ((pos.x + dim.x - 1) >= paramPosition.x)
			&& (pos.y <= paramPosition.y) && ((pos.y + dim.y - 1) >= paramPosition.y))
			return objs[i];
	}
	return nullptr;
}

int Card::GetCardNumber(Position paramPosition) {
	GameObject* cardObj = Card::GetCardObject(paramPosition);
	if (cardObj == nullptr) return 0;
	Card* card = dynamic_cast<Card*>(cardObj);
	if (card == nullptr) return 0;
	return card->getNumber();
	/*
	for (int i = 0; i < max_objs; i++)
	{
		if (objs[i] == nullptr) continue;
		Vector2 pos = objs[i]->getPosition();
		Dimension dim = objs[i]->getDimension();
		if ((pos.x <= mousePosition.x) && ((pos.x + dim.x - 1) >= mousePosition.x))
		{
			if ((pos.y <= mousePosition.y) && ((pos.y + dim.y - 1) >= mousePosition.y)) {
				Card* card = dynamic_cast<Card*>(objs[i]);
				if (card == nullptr) continue;
				return card->getNumber();
			}
		}
	}
	*/
}

int Card::GetCardNumber(Vector2 paramPosition) {
	GameObject* cardObj = Card::GetCardObject(paramPosition);
	if (cardObj == nullptr) return 0;
	Card* card = dynamic_cast<Card*>(cardObj);
	if (card == nullptr) return 0;
	return card->getNumber();
}

int Card::GetCardNumber(GameObject* obj) {
	GameObject* cardObj = obj;
	if (cardObj == nullptr) return 0;
	Card* card = dynamic_cast<Card*>(cardObj);
	if (card == nullptr) return 0;
	return card->getNumber();
}

void Card::update(InputManager& input, GameManager& gameManager)
{
	if (input.getMouseButtonDown(0)) {
		auto mousePos = input.getMousePosition();
		GameObject* downObject = Card::GetCardObject(mousePos);
		if (downObject != nullptr) gameManager.setMouseDownObject(downObject);
	}
	if (input.getMouseButton(0)) {
		auto mousePos = input.getMousePosition();
	}
	if (input.getMouseButtonUp(0)) {
		auto mousePos = input.getMousePosition();
		GameObject* upObject = Card::GetCardObject(mousePos);
		if (upObject != nullptr) gameManager.setMouseUpObject(upObject);
		if (upObject != nullptr
			&& upObject != gameManager.getMouseDownObject()
			&& sqrDistance(upObject->getPosition(), gameManager.getMouseDownObject()->getPosition()) <= 7.0f) {
			Card::swapCard(upObject, gameManager.getMouseDownObject());
			//Debug::Log("Card Changed!");
		}
	}
}

void Card::swapCard(GameObject* destination, GameObject* source) {
	Card* destCard = dynamic_cast<Card*>(destination);
	Card* sourceCard = dynamic_cast<Card*>(source);
	if (destCard == nullptr || sourceCard == nullptr) return;
	Card tempCard = *destCard;
	destCard->setNumber(sourceCard);
	sourceCard->setNumber(&tempCard);
}