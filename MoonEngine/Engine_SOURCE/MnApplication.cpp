#include "MnApplication.h"
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
	}

	void Application::Initialize()
	{
	}

	void Application::Update()
	{
	}

	void Application::LateUpdate()
	{
	}

	void Application::Render()
	{
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			_Hwnd = hwnd;
			_Width = width;
			_Height = height;

			graphicDevice = std::make_unique<Mn::graphics::GraphicDevice_Dx11>();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(_Hwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(_Hwnd, true);
		UpdateWindow(_Hwnd);
	}
}