#include "MnWaterWave.h"
#include "MnWaterWaveRender.h"

namespace Mn
{
	WaterWave::WaterWave()
	{
	}
	WaterWave::~WaterWave()
	{
	}
	void WaterWave::Initialize()
	{
		WaterWaveRender* WWR = AddComponent<WaterWaveRender>();
		GameObject::Initialize();
	}
	void WaterWave::Update()
	{
		GameObject::Update();
	}
	void WaterWave::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void WaterWave::Render()
	{
		GameObject::Render();
	}
}