#include "MnWaterScript.h"

namespace Mn
{
	WaterScript::WaterScript()
		: _Time(0.0f)
	{
	}
	WaterScript::~WaterScript()
	{
	}
	void WaterScript::Initialize()
	{
		_Time = Time::DeltaTime();
	}
	void WaterScript::Update()
	{

	}
	void WaterScript::LateUpdate()
	{
		_Time += Time::DeltaTime();
		_Times = Vector4(_Time, _Time/2.0f, 0.0f, 0.0f);
	}
	void WaterScript::Render()
	{
		BindConstantbuffer();
	}
	void WaterScript::BindConstantbuffer()
	{
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Time];
		cb->setData(&_Times);
		cb->Bind(eShaderStage::PS);
	}
}