#include "WindowsWindow.hpp"

#include <Windowsx.h>

#include "../../Application.hpp"

#include "../../../Gameplay/InputManager.hpp"

namespace DadEngine::Core
{
	LRESULT WindowProcedure(HWND _InHWND, uint32 _InMsg, WPARAM _InWParam, LPARAM _InLParam)
	{
		Application::GetApp()->m_window.HandleMessages(_InHWND, _InMsg, _InWParam, _InLParam);

		return DefWindowProc(_InHWND, _InMsg, _InWParam, _InLParam);
	}
	
	void WindowsWindow::HandleMessages(HWND _InHWND, uint32 _InMsg, WPARAM _InWParam, LPARAM _InLParam)
	{
		switch (_InMsg)
		{
			case WM_SIZE:
			{
				//uint32 uiWidth = LOWORD(_InLParam);
				//uint32 uiHeight = HIWORD(_InLParam);

				//OnSize(_InHWND, uiWidth, uiHeight);
				//GetClientRect(_InHWND, );

				break;
			}

			case WM_PAINT:
				break;

			case WM_CLOSE:
			{
				DestroyWindow(_InHWND);
				break;
			}

			case WM_QUIT:
			{
				PostQuitMessage(0);
				break;
			}

			case WM_DESTROY:
			{
				PostQuitMessage(0);
				break;
			}

			case WM_KEYDOWN:
			{
				//printf("%d\n", MapVirtualKey((UINT)_InWParam, MAPVK_VK_TO_CHAR));

				Gameplay::InputManager::GetInputManager()->UpdateKeyState((Gameplay::KeyCode)MapVirtualKey((UINT)_InWParam, MAPVK_VK_TO_CHAR), Gameplay::KEY_STATE_KEY_PRESSED);
				
				break;
			}

			case WM_KEYUP:
			{
				Gameplay::InputManager::GetInputManager()->UpdateKeyState((Gameplay::KeyCode)MapVirtualKey((UINT)_InWParam, MAPVK_VK_TO_CHAR), Gameplay::KEY_STATE_KEY_RELEASED);

				break;
			}

			case WM_LBUTTONDOWN:
			{
				Gameplay::InputManager::GetInputManager()->UpdateButtonState(Gameplay::BUTTON_LEFT_BUTTON, Gameplay::BUTTON_STATE_BUTTON_DOWN);
				break;
			}

			case WM_LBUTTONUP:
			{
				Gameplay::InputManager::GetInputManager()->UpdateButtonState(Gameplay::BUTTON_LEFT_BUTTON, Gameplay::BUTTON_STATE_BUTTON_UP);
				break;
			}

			case WM_RBUTTONDOWN:
			{
				Gameplay::InputManager::GetInputManager()->UpdateButtonState(Gameplay::BUTTON_RIGHT_BUTTON, Gameplay::BUTTON_STATE_BUTTON_DOWN);
				break;
			}

			case WM_RBUTTONUP:
			{
				Gameplay::InputManager::GetInputManager()->UpdateButtonState(Gameplay::BUTTON_RIGHT_BUTTON, Gameplay::BUTTON_STATE_BUTTON_UP);
				break;
			}

			case WM_MBUTTONDOWN:
			{
				Gameplay::InputManager::GetInputManager()->UpdateButtonState(Gameplay::BUTTON_MIDDLE_BUTTON, Gameplay::BUTTON_STATE_BUTTON_DOWN);
				break;
			}

			case WM_MBUTTONUP:
			{
				Gameplay::InputManager::GetInputManager()->UpdateButtonState(Gameplay::BUTTON_MIDDLE_BUTTON, Gameplay::BUTTON_STATE_BUTTON_UP);
				break;
			}

			case WM_MOUSEMOVE:
			{
				Gameplay::InputManager::GetInputManager()->UpdateMousePosition(GET_X_LPARAM(_InLParam), GET_Y_LPARAM(_InLParam));
				break;
			}

			case WM_MOUSEWHEEL:
			{
				Gameplay::InputManager::GetInputManager()->UpdateWheelDelta(GET_WHEEL_DELTA_WPARAM(_InWParam));
				break;
			}
		}
	}
}