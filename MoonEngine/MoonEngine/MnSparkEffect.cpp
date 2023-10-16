#include "MnSparkEffect.h"
#include "MnSparkRender.h"
#include "MnSparkScript.h"

namespace Mn
{
	SparkEffect::SparkEffect()
	{
	}
	SparkEffect::~SparkEffect()
	{
	}
	void SparkEffect::Initialize()
	{
		SparkRender* SR = AddComponent<SparkRender>();
		SparkScript* SS = AddComponent<SparkScript>();
		GameObject::Initialize();
	}
	void SparkEffect::Update()
	{
		GameObject::Update();
	}
	void SparkEffect::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void SparkEffect::Render()
	{
		GameObject::Render();
	}
}