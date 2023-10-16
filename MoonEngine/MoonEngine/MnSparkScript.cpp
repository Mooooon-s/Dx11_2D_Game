#include "MnSparkScript.h"
#include "MnGameObject.h"
#include "MnAnimator.h"

namespace Mn
{
	SparkScript::SparkScript()
	{
	}
	SparkScript::~SparkScript()
	{
	}
	void SparkScript::Initialize()
	{
	}
	void SparkScript::Update()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		if (at->AnimationComplete())
			GetOwner()->State(GameObject::eState::Dead);
	}
	void SparkScript::LateUpdate()
	{
	}
	void SparkScript::Render()
	{
	}
}