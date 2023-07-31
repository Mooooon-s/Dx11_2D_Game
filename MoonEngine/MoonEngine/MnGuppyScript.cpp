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
		_Tree = new GuppyBehaviorTree(GetOwner());
		_Tree->Initialize();
	}
	void GuppyScript::Update()
	{
		_Tree->Run();
		/*if (Input::GetKeyDown(eKeyCode::A))
		{
			if (_Dir == eDir::Left)
				_Dir = eDir::Right;
			else
				_Dir = eDir::Left;
			GetOwner()->GetComponent<GuppyAnimationCntrl>()->Play();
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			_Level += 1;
			GetOwner()->GetComponent<GuppyAnimationCntrl>()->Play();
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			_Level -= 1;
			GetOwner()->GetComponent<GuppyAnimationCntrl>()->Play();
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			_Hungry = true;
			GetOwner()->GetComponent<GuppyAnimationCntrl>()->Play();
		}
		if (Input::GetKeyDown(eKeyCode::E))
		{
			_Hungry = false;
			GetOwner()->GetComponent<GuppyAnimationCntrl>()->Play();
		}
		if (Input::GetKeyDown(eKeyCode::R))
		{
			_Behavior = eBehavior::Turn;
			GetOwner()->GetComponent<GuppyAnimationCntrl>()->Play();
		}*/
		//Swim();
	}
	void GuppyScript::LateUpdate()
	{

	}
	void GuppyScript::Render()
	{
	}
	void GuppyScript::Behavior()
	{
	}
	void GuppyScript::Think()
	{
	}
	void GuppyScript::Swim()
	{
		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		MoveVec();
		pos += _Move * _Speed * Time::DeltaTime();
		tr->Position(pos);*/
	}
	void GuppyScript::MoveVec()
	{
		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->Position();
		if (_Dir == eDir::Left)
			if(pos.x > -2.0f && pos.x<2.0 && pos.y>-3.0f && pos.y < 2.0f)
				_Move = Vector3(-1.0f, 0.0f, 0.0f);
			else
				_Move = Vector3(0.0f, 0.0f, 0.0f);
		else
			if (pos.x > -2.0f && pos.x<2.0 && pos.y>-3.0f && pos.y < 2.0f)
				_Move = Vector3(1.0f, 0.0f, 0.0f);
			else
				_Move = Vector3(0.0f, 0.0f, 0.0f);*/
	}
}