#pragma once

#include "Card.h"

class GameManager
{
private:
	GameObject* mouseDownObject;
	GameObject* mouseUpObject;

	void countColumn(GameObject* source, int& count) {
		Card* obj = dynamic_cast<Card*>(source);
		if (source == nullptr) return;

		Vector2 objPos = obj->getPosition();
		Dimension objDim = obj->getDimension();
		Vector2 targetPos = { objPos.x, objPos.y + objDim.y };
		if (Card::GetCardObject(targetPos) == nullptr) return;
		if (obj->getNumber() == Card::GetCardNumber(targetPos)) {
			count++;
			countColumn(Card::GetCardObject(targetPos), count);
		}
		if (count >= 3) return;
		count = 1;
	}
	void countRow(GameObject* source, int& count) {
		Card* obj = dynamic_cast<Card*>(source);
		if (source == nullptr) return;

		Vector2 objPos = obj->getPosition();
		Dimension objDim = obj->getDimension();
		Vector2 targetPos = { objPos.x + objDim.x, objPos.y };
		if (Card::GetCardObject(targetPos) == nullptr) return;
		if (obj->getNumber() == Card::GetCardNumber(targetPos)) {
			count++;
			countRow(Card::GetCardObject(targetPos), count);
		}
		if (count >= 3) return;
		count = 1;
	}

public:
	GameManager() : mouseDownObject(nullptr), mouseUpObject(nullptr)
	{};

	GameObject* getMouseDownObject() const { return this->mouseDownObject; }
	void setMouseDownObject(GameObject* obj) { this->mouseDownObject = obj; }
	
	GameObject* getMouseUpObject() const { return this->mouseUpObject; }
	void setMouseUpObject(GameObject* obj) { this->mouseUpObject = obj; }

	// Column
	void checkMatchColumn(const float xPos, const int size) {
		int count = 1;
		for (float yPos = 0.0f; yPos <= (size - 1) * 7.0f; yPos += 7.0f) {
			//Debug::Log("Checking %d Row", (int)xPos);
			Vector2 pos = { xPos, yPos };
			countColumn(Card::GetCardObject(pos), count);
			if (count >= 3) {
				for (float i = yPos; i <= yPos + (7.0f * (count - 1)); i += 7.0f) {
					Vector2 removePos = { xPos, i };
					GameObject* destroyObj = Card::GetCardObject(removePos);
					if (destroyObj == nullptr) continue;
					destroyObj->setAlive(false);
					Debug::Log("Column Object Destroyed! <CardNum: %d> [%d, %d]", Card::GetCardNumber(destroyObj), (int)destroyObj->getPosition().x, (int)destroyObj->getPosition().y);
				}
				count = 1;
				break;
			}
		}
	}
	void checkMatchAllColumns(const int size) {
		for (int i = 0; i < size; i++) {
			float xPos = i * 5.0f;
			checkMatchColumn(xPos, size);
		}
	}
	// Row
	void checkMatchRow(const float yPos, const int size) {
		int count = 1;
		for (float xPos = 0.0f; xPos <= (size - 1) * 5.0f; xPos += 5.0f) {
			//Debug::Log("Checking %d Column", (int)yPos);
			Vector2 pos = { xPos, yPos };
			countRow(Card::GetCardObject(pos), count);
			if (count >= 3) {
				for (float i = xPos; i <= xPos + (5.0f * (count - 1)); i += 5.0f) {
					Vector2 removePos = { i, yPos };
					GameObject* destroyObj = Card::GetCardObject(removePos);
					if (destroyObj == nullptr) continue;
					destroyObj->setAlive(false);
					Debug::Log("Row Object Destroyed! <CardNum: %d> [%d, %d]", Card::GetCardNumber(destroyObj), (int)destroyObj->getPosition().x, (int)destroyObj->getPosition().y);
				}
				count = 1;
				break;
			}
		}
	}
	void checkMatchAllRows(const int size) {
		for (int i = 0; i < size; i++) {
			float yPos = i * 7.0f;
			checkMatchRow(yPos, size);
		}
	}
	// All
	void checkMatch(const MatrixSize& size) {
		checkMatchAllColumns(size.rows);
		checkMatchAllRows(size.columns);
	}


	~GameManager() {};
};

