#include <iostream>
#include <cstdlib> // include rand()
#include <Windows.h>
#include <conio.h>

#include "GameObject.h"
#include "Utils.h"
#include "InputManager.h"
#include "GameManager.h"


int main()
{

	GameObject::Initialize();
    InputManager input;
	GameManager gameManager;
	
	bool exit_flag = false;
    
	while (exit_flag == false)
	{
		GameObject::ClearFrame();
		input.readEveryFrame();

		GameObject::ProcessInput(exit_flag, input);

		GameObject::ExamineMatch(gameManager);

		GameObject::FillObjectAtEmpty();

		GameObject::UpdateAll(input, gameManager);
		
		GameObject::DrawAll();

		GameObject::RenderFrame();
	}

    GameObject::Deinitialize();

	return 0;
}

