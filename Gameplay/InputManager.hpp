#ifndef __INPUT_MANAGER_HPP_
#define __INPUT_MANAGER_HPP_

#include "../Core/Core.hpp"

namespace DadEngine::Gameplay
{
	enum KeyState
	{
		KEY_STATE_KEY_PRESSED,
		KEY_STATE_KEY_DOWN = 0xf000,
		KEY_STATE_KEY_UP,
		KEY_STATE_KEY_RELEASED,
		MAX_KEY_STATE
	};

	enum ButtonState
	{
		BUTTON_STATE_BUTTON_DOWN,
		BUTTON_STATE_BUTTON_PRESSED,
		BUTTON_STATE_BUTTON_UP,
		BUTTON_STATE_BUTTON_RELEASED,
		BUTTON_STATE_WHEEL_SCROLL_UP,
		BUTTON_STATE_WHEEL_SCROLL_DOWN,
		MAX_BUTTON_STATE
	};

	enum MouseButton
	{
		BUTTON_LEFT_BUTTON,
		BUTTON_RIGHT_BUTTON,
		BUTTON_MIDDLE_BUTTON,
		MAX_BUTTON
	};

	enum KeyCode
	{
		KEY_A = 65,
		KEY_D = 68,
		KEY_S = 83,
		KEY_W = 87,
		MAX_KEY_CODE = 255
	};

	struct Key
	{
		Key() = default;

		Key(KeyCode _InBindedKey)
			: m_KeyIndex(_InBindedKey)
		{}

		KeyState m_State = MAX_KEY_STATE;
		KeyCode m_KeyIndex = MAX_KEY_CODE;
		uint8_t m_IsConsumed = FALSE;
	};

	struct Button
	{
		Button() = default;

		Button(MouseButton _InButton)
			:m_Button(_InButton)
		{}

		MouseButton m_Button = MAX_BUTTON;
		ButtonState m_State = MAX_BUTTON_STATE;
        uint8_t m_IsConsumed = FALSE;
	};


	struct Input
	{
		Input() = default;

		Input(KeyCode _InKeyCode)
		{
			m_KeysCodes.Add(_InKeyCode);
		}

		Input(MouseButton _InButton)
		{
			m_MouseButtons.Add(_InButton);
		}


		virtual void Action() = 0;


		TArray<MouseButton> m_MouseButtons;
		TArray<KeyCode> m_KeysCodes;
	};


	class InputManager
	{

	public:

		InputManager() = default;

		~InputManager() = default;


		static InputManager* GetInputManager();


		void UpdateKeyState(KeyCode _InKeyCode, KeyState _InNewState)
		{
			// Key is pressed again
			if ((m_Keys[_InKeyCode].m_State == KEY_STATE_KEY_PRESSED
				&& _InNewState == KEY_STATE_KEY_PRESSED)
				|| (m_Keys[_InKeyCode].m_State == KEY_STATE_KEY_DOWN
					&& _InNewState == KEY_STATE_KEY_PRESSED))
			{
				m_Keys[_InKeyCode].m_State = KEY_STATE_KEY_DOWN;
			}

			// Key is released again
			else if ((m_Keys[_InKeyCode].m_State == KEY_STATE_KEY_RELEASED
				&& _InNewState == KEY_STATE_KEY_RELEASED)
				|| (m_Keys[_InKeyCode].m_State == KEY_STATE_KEY_UP
				&& _InNewState == KEY_STATE_KEY_RELEASED))
			{
				m_Keys[_InKeyCode].m_State = KEY_STATE_KEY_UP;
			}

			else
			{
				m_Keys[_InKeyCode].m_State = _InNewState;
			}

			m_Keys[_InKeyCode].m_IsConsumed = FALSE;
		}

		void UpdateButtonState(MouseButton _InButton, ButtonState _InNewState)
		{
			// Button is pressed again
			if ((m_MouseButtons[_InButton].m_State == BUTTON_STATE_BUTTON_PRESSED
				&& _InNewState == BUTTON_STATE_BUTTON_PRESSED)
				|| (m_MouseButtons[_InButton].m_State == BUTTON_STATE_BUTTON_DOWN
					&& _InNewState == BUTTON_STATE_BUTTON_PRESSED))
			{
				m_MouseButtons[_InButton].m_State = BUTTON_STATE_BUTTON_PRESSED;
			}

			// Button is released again
			else if ((m_MouseButtons[_InButton].m_State == BUTTON_STATE_BUTTON_RELEASED
				&& _InNewState == BUTTON_STATE_BUTTON_RELEASED)
				|| (m_MouseButtons[_InButton].m_State == BUTTON_STATE_BUTTON_UP
					&& _InNewState == BUTTON_STATE_BUTTON_RELEASED))
			{
				m_MouseButtons[_InButton].m_State = BUTTON_STATE_BUTTON_UP;
			}

			else
			{
				m_MouseButtons[_InButton].m_State = _InNewState;
			}

			m_MouseButtons[_InButton].m_IsConsumed = FALSE;
		}

		void UpdateMousePosition(int32_t _InX, int32_t _InY)
		{
			m_PosX = _InX;
			m_PosY = _InY;
		}

		void UpdateWheelDelta(int16_t _InWheelDelta)
		{
			m_WheelDelta = _InWheelDelta;
		}


		void Update()
		{
			for (Input* currentInput : m_Inputs)
			{
				for (KeyCode& currentKey : currentInput->m_KeysCodes)
				{
					//printf("%d\n", Application::GetApp()->GetWindow().KeyState(currentKey));

					// Update keys
					if (/*Application::GetApp()->GetWindow().KeyState(currentKey) & KEY_STATE_KEY_DOWN*/m_Keys[currentKey].m_IsConsumed == FALSE
						&& (m_Keys[currentKey].m_State == KEY_STATE_KEY_DOWN
							|| m_Keys[currentKey].m_State == KEY_STATE_KEY_PRESSED))
					{
						currentInput->Action();
						m_Keys[currentKey].m_IsConsumed = TRUE;
					}
				}

				for (MouseButton& currMouseBtn : currentInput->m_MouseButtons)
				{
					// Update buttons
					if (m_MouseButtons[currMouseBtn].m_IsConsumed == FALSE
						&& (m_MouseButtons[currMouseBtn].m_State == KEY_STATE_KEY_DOWN
							|| m_MouseButtons[currMouseBtn].m_State == KEY_STATE_KEY_PRESSED))
					{
						currentInput->Action();
						m_MouseButtons[currMouseBtn].m_IsConsumed = TRUE;
					}
				}
			}
		}


		TArray<Input*> m_Inputs;


	private:

		int32_t m_PosX = 0, m_PosY = 0;
		int16_t m_WheelDelta = 0;
		Button m_MouseButtons[MAX_BUTTON]{};
		Key m_Keys[MAX_KEY_CODE]{};
	};
}

#endif //!__INPUT_MANAGER_HPP_