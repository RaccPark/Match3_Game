#include <cstdlib> // include rand()
#include <Windows.h>
#include <conio.h>
#include "GameManager.h"
#include "GameObject.h"
#include "ICollidable.h"
#include "Canvas.h"
#include "InputManager.h"

Canvas GameObject::canvas(46, 49);	// Screen Size
MatrixSize GameObject::matrix(7, 9); // Matrix Size
int GameObject::max_objs = (GameObject::matrix.columns * GameObject::matrix.rows);
GameObject** GameObject::objs = new GameObject * [GameObject::max_objs];

void GameObject::draw() { if (alive == true) canvas.draw(shape, position, dimension, visible); }

void GameObject::Initialize()
{

	for (int i = 0; i < max_objs; i++)
		objs[i] = nullptr;

	auto dim = canvas.getDimension();

	// Add NumberCard
	GameObject::FillObjectAtEmpty();
}

void GameObject::Add(GameObject* obj)
{
	if (obj == nullptr) return;

	for (int i = 0; i < max_objs; i++)
	{
		if (objs[i] != nullptr) continue;
		objs[i] = obj;
		break; 
	}
}

void GameObject::FillObjectAtEmpty()
{
	Vector2 spawnPos = { 0.0f, 0.0f };
	for (int i = 0; i < max_objs; i++) {
		if (Card::GetCardObject(spawnPos) == nullptr) {
			int randNum = rand() % 5;
			switch (randNum)
			{
			case 0:
				GameObject::Add(new Card("       #    #    #    #    #       ", spawnPos, Dimension{ 5, 7 }, true, 1)); // 1
				break;
			case 1:
				GameObject::Add(new Card("      ###    #  ###  #    ###      ", spawnPos, Dimension{ 5, 7 }, true, 2)); // 2
				break;
			case 2:
				GameObject::Add(new Card("      ###    #  ###    #  ###      ", spawnPos, Dimension{ 5, 7 }, true, 3)); // 3
				break;
			case 3:
				GameObject::Add(new Card("      # #  # #  ###    #    #      ", spawnPos, Dimension{ 5, 7 }, true, 4)); // 4
				break;
			case 4:
				GameObject::Add(new Card("      ###  #    ###    #  ###      ", spawnPos, Dimension{ 5, 7 }, true, 5)); // 5
				break;
			}
			Debug::Log("Spawn <%d> At: [%d, %d]", randNum + 1, (int)spawnPos.x, (int)spawnPos.y);
		}
		spawnPos.x += 5.0f;
		if (spawnPos.x == 5.0f * matrix.rows) {
			spawnPos.x = 0.0f;
			spawnPos.y += 7.0f;
			continue;
		}
		if (spawnPos.y == 7.0f * matrix.columns)	break;
	}
}

void GameObject::Remove(GameObject* obj)
{
	if (obj == nullptr) return;

	for (int i = 0; i < max_objs; i++)
	{
		if (obj == objs[i]) continue;

		delete objs[i];
		objs[i] = nullptr;
		return;
	}
}

void GameObject::ClearFrame()
{
	canvas.clear();
}

void GameObject::ProcessInput(bool& exit_flag, InputManager& input)
{
	if (input.getKeyDown(0x51)) { // 'q'
		exit_flag = true;
	}
}

void GameObject::UpdateAll(InputManager& input, GameManager& gameManager)
{
	for (int i = 0; i < max_objs; i++)
	{
		if (objs[i] == nullptr || objs[i]->isAlive() == false) continue;
		objs[i]->update(input, gameManager);
	}
	RemoveDeadObjects();
}

void GameObject::DrawAll()
{
	for (int i = 0; i < max_objs; i++)
	{
		if (objs[i] == nullptr) continue;
		objs[i]->draw();
	}
}

void GameObject::RenderFrame()
{
	canvas.render();
	Sleep(10);
}

void GameObject::ExamineCollision()
{
	for (int i = 0; i < max_objs; i++)
	{
		if (objs[i] == nullptr) continue;
		if (objs[i]->isAlive() == false) continue;
		ICollidable* c_i = dynamic_cast<ICollidable*>(objs[i]);
		if (c_i == nullptr) continue;
		for (int j = i + 1; j < max_objs && objs[i]->isAlive() == true; j++)
		{
			if (objs[j] == nullptr) continue;
			if (objs[j]->isAlive() == false) continue;
			ICollidable* c_j = dynamic_cast<ICollidable*>(objs[j]);
			if (c_j == nullptr) continue;
			if (objs[i]->isColliding(objs[j]) == false)  continue;
			c_j->onCollision(objs[i]);
			c_i->onCollision(objs[j]);
		}
	}
	RemoveDeadObjects();
}

void GameObject::ExamineMatch(GameManager& gameManager)
{
	gameManager.checkMatch(GameObject::matrix);

	RemoveDeadObjects();
}

void GameObject::RemoveDeadObjects()
{
	for (int i = 0; i < max_objs; i++)
	{
		if (objs[i] == nullptr) continue;
		if (objs[i]->isAlive() == true) continue;
		delete objs[i];
		objs[i] = nullptr;
	}
}

void GameObject::Deinitialize()
{
	for (int i = 0; i < max_objs; i++)
	{
		if (objs[i] == nullptr) continue;
		delete objs[i];
		objs[i] = nullptr;
	}
	delete[] objs;
}

