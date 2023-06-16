#include "MnLayer.h"
namespace Mn
{
	Layer::Layer()
		:Layer()
	{
	}
	Layer::~Layer()
	{
	}
	void Layer::Initialize()
	{
		for (auto gameObj : _GameObjects)
		{
			gameObj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (auto gameObj : _GameObjects)
		{
			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (auto gameObj : _GameObjects)
		{
			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (auto gameObj : _GameObjects)
		{
			gameObj->Render();
		}
	}
}