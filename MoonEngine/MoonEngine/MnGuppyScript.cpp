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

#include "MnResources.h"
#include "MnAudioClip.h"


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
		Resources::Load<Mn::AudioClip>(L"Eat_Food", L"..\\Resources\\Sound\\SLURP.ogg");
		Resources::Load<Mn::AudioClip>(L"Grow", L"..\\Resources\\Sound\\grow.wav");
		Resources::Load<Mn::AudioClip>(L"Splash", L"..\\Resources\\Sound\\SPLASH.ogg");
	}
	void GuppyScript::Update()
	{
	}
	void GuppyScript::LateUpdate()
	{
	}
	void GuppyScript::Render()
	{
	}
}