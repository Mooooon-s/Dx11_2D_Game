#include "MnGuppyScript.h"
#include "MnGuppy.h"
#include "MnAnimator.h"
#include "MnTime.h"
#include <random>
namespace Mn
{
	GuppyScript::GuppyScript()
		: _Behavior(eBehavior::Swim)
		, _Time(0.0f)
		, _Level(1)
		, _Speed(0.8f)
		, _Hungry(false)
		, _Dir(eDir::Right)
		, _Move(Vector3::Right)
	{
		
	}
	GuppyScript::~GuppyScript()
	{

	}
	void GuppyScript::Initialize()
	{

	}
	void GuppyScript::Update()
	{
		Behavior();
		switch (_Behavior)
		{
		case eBehavior::Swim:
			Swim();
			break;
		case eBehavior::Turn:
			Turn();
			break;
		case eBehavior::Eat:
			Eat();
			break;
		case eBehavior::End:
			break;
		default:
			break;
		}
	}
	void GuppyScript::LateUpdate()
	{

	}
	void GuppyScript::Render()
	{

	}
	void GuppyScript::Behavior()
	{
		_Time += Time::DeltaTime();

		if (_Time >= 3.0f)
		{
			Think();

			if (_Behavior == eBehavior::Turn)
			{
				if (_Dir == eDir::Left)
					_Dir = eDir::Right;
				else
					_Dir = eDir::Left;
			}
			_Time = 0;
		}
	}
	void GuppyScript::Think()
	{

		Guppy* guppy = dynamic_cast<Guppy*>(GetOwner());
		eFishState state = guppy->GetFishState();
		if (state== eFishState::Hungry || state== eFishState::Starving)
			return;
		std::random_device rd;
		std::mt19937 engine(rd());
		std::uniform_real_distribution<float> num(0.0f, 12.0f);
		std::vector<float> v;

		v.push_back(num(engine));
		Animator* at = guppy->GetComponent<Animator>();
		switch ((int)v[0])
		{
		case 0:
			at->PlayAnimation(L"Swim_Small", true);
			break;
		case 1:
			at->PlayAnimation(L"Swim_Middle", true);
			break;
		case 2:
			at->PlayAnimation(L"Swim_Large", true);
			break;
		case 3:
			at->PlayAnimation(L"Hungry_Swim_Small", true);
			break;					  
		case 4:						  
			at->PlayAnimation(L"Hungry_Swim_Middle", true);
			break;					  
		case 5:						  
			at->PlayAnimation(L"Hungry_Swim_Large", true);
			break;
		case 6:
			at->PlayAnimation(L"Turn_Small", true);
			break;
		case 7:
			at->PlayAnimation(L"Turn_Middle", true);
			break;
		case 8:
			at->PlayAnimation(L"Turn_Large", true);
			break;
		case 9:
			at->PlayAnimation(L"Hungry_Turn_Small", true);
			break;
		case 10:
			at->PlayAnimation(L"Hungry_Turn_Middle", true);
			break;
		case 11:
			at->PlayAnimation(L"Hungry_Turn_Large", true);
			break;
		default:
			break;
		}
		
	}
	void GuppyScript::Swim()
	{
		Guppy* guppy = dynamic_cast<Guppy*>(GetOwner());
		eFishState state = guppy->GetFishState();
		if (state == eFishState::Hungry)
			_Behavior = eBehavior::Eat;

		Transform* tr = guppy->GetComponent<Transform>();
		Vector3 pos = tr->Position();

		if (pos.x > -2.0f && pos.x<2.0 && pos.y>-3.0f && pos.y < 2.0f)
		{
			pos += _Move * _Speed * Time::DeltaTime();
		}
		else
		{
			pos = tr->Position();
		}
		tr->Position(pos);
	}
	void GuppyScript::Turn()
	{
		Guppy* guppy = dynamic_cast<Guppy*>(GetOwner());
		Animator* at = GetOwner()->GetComponent<Animator>();
		Transform* tr = guppy->GetComponent<Transform>();
		Vector3 pos = tr->Position();

		pos += _Move * _Speed * Time::DeltaTime();
		tr->Position(pos);

		if (_Hungry)
		{

			if (at->AnimationComplete())
				_Behavior = eBehavior::Eat;
		}
		else
		{
			if (at->AnimationComplete())
				_Behavior = eBehavior::Swim;
		}

	}
	void GuppyScript::MoveVec()
	{
		if (_Hungry)
		{
			//move to food
		}
		else
		{
			if (_Dir == eDir::Left)
				_Move = Vector3(-1.0f, 0.1f, 0.0f);
			else
				_Move = Vector3(1.0f, 0.1f, 0.0f);
		}
	}
	void GuppyScript::Eat()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();
		if (at->AnimationComplete())
			_Behavior = eBehavior::Swim;
	}
}