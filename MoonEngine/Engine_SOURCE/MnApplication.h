#pragma once
#include "MoonEngine.h"
#include "MnGraphicDevice_Dx11.h"
#include "MnScene.h"

namespace Mn
{
	class Application
	{
	private:
		std::unique_ptr<Mn::graphics::GraphicDevice_Dx11> graphicDevice;
		bool _Initialize = false;
		HWND _Hwnd;
		UINT _Width;
		UINT _Height;

		Scene* _Scene;
	public:
		Application();
		~Application();
	public:
		void Run();
		void Initialize();
		void Update();
		void LateUpdate();
		void Render();
	public:
		void SetWindow(HWND hwnd,UINT width,UINT height);
	public:
		UINT GetWidth() { return _Width; }
		UINT GetHeight() { return _Height; }
		HWND GetHwnd() { return _Hwnd; }
	};
}

