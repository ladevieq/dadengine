#include "InputManager.hpp"

namespace DadEngine::Gameplay
{
	InputManager* s_InputManager = new InputManager();


	InputManager* InputManager::GetInputManager()
	{
		return s_InputManager;
	}
}