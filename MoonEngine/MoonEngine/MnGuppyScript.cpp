#include "MnGuppyScript.h"
#include <random>

#include "MnRenderer.h"
#include "MnAnimator.h"
#include "MnConstantBuffer.h"

#include "MnTime.h"
#include "MnInput.h"

#include "MnGuppy.h"
#include "MnGuppyAnimationCntrl.h"

#include "MnGuppyBehaviorTree.h"


namespace Mn
{
	GuppyScript::GuppyScript()
		: _Behavior(eBehavior::Turn)
		, _Time(0.0f)
		, _Level(1)
		, _Speed(0.8f)
		, _Hungry(false)
		, _Dir(eDir::Left)
		, _Move(Vector3::Left)
	{
		
	}
	GuppyScript::~GuppyScript()
	{

	}
	void GuppyScript::Initialize()
	{
		/*_Tree = new GuppyBehaviorTree(GetOwner());
		_Tree->Initialize();*/
	}
	void GuppyScript::Update()
	{
		//_Tree->Run();
	}
	void GuppyScript::LateUpdate()
	{

	}
	void GuppyScript::Render()
	{
	}
}