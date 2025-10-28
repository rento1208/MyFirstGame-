#include "Input.h"
#include <vector>
#include <fbxsdk.h>
#include <DirectXmath.h>
#pragma comment(lib, "dxguid.lib")


namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256];    //前フレームでの各キーの状態

	HWND hWnd = nullptr;
	LPDIRECTINPUTDEVICE8 pMouseDevice = nullptr;
	DIMOUSESTATE prevMouseState;
	DIMOUSESTATE mouseState;
	XMVECTOR mousePosition;


	void Initialize(HWND hwnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&pDInput, nullptr);

		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice, nullptr);
		pMouseDevice->SetDataFormat(&c_dfDIMouse);
		pMouseDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}


	void Update()
	{
		// キーボード
		memcpy(prevKeyState, keyState, sizeof(keyState));
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);

		// マウス
		prevMouseState = mouseState;
		pMouseDevice->Acquire();
		pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0X80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//今は押してて、前回は押してない
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0X80))
		{
			return true;
		}
		return false;
	}


	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0X80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButton(int button)
	{
		if (mouseState.rgbButtons[button] & 0X80)
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonUp(int button)
	{
		return (!(mouseState.rgbButtons[button] & 0x80) && (prevMouseState.rgbButtons[button] & 0x80));
	}

	bool IsMouseButtonDown(int button)
	{
		return ((mouseState.rgbButtons[button] & 0x80) && !(prevMouseState.rgbButtons[button] & 0x80));
	}

	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
		SAFE_RELEASE(pKeyDevice);
	}


}