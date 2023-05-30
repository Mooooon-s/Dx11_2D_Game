#include "MnApplication.h"
#include "MnTime.h"
#include "MnInput.h"
#include "MnRenderer.h"

namespace Mn
{
	Application::Application()
		: graphicDevice(nullptr)
		, _Hwnd(NULL)
		, _Width(-1)
		, _Height(-1)
	{

	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Initialize()
	{
		Time::Initialize();
		Input::Initialize();

		renderer::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Updatae();
	}

	void Application::LateUpdate()
	{
	}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->Draw();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			_Hwnd = hwnd;
			_Width = width;
			_Height = height;

			graphicDevice = std::make_unique<Mn::graphics::GraphicDevice_Dx11>();
			Mn::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(_Hwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(_Hwnd, true);
		UpdateWindow(_Hwnd);
	}
}