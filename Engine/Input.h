#pragma once

#include <dInput.h>
#include <vector>
#include <DirectXMath.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}
using namespace DirectX;
namespace Input
{
	void Initialize(HWND hwnd);
	void Update();
	bool IsKey(int keyCode);
	bool IsKeyUp(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsMouseButton(int button);
	bool IsMouseButtonUp(int button);
	bool IsMouseButtonDown(int button);
	void Release();
	XMVECTOR GetMousePosition();
	void SetMousePosition(int x, int y);


};