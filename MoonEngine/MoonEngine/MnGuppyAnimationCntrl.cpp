#include "MnGuppyAnimationCntrl.h"
#include "MnGameObject.h"
#include "MnGuppyScript.h"
#include "MnMeshRenderer.h"
#include "MnMaterial.h"
#include "MnResources.h"
#include "MnAnimator.h"

namespace Mn
{
	GuppyAnimationCntrl::GuppyAnimationCntrl()
		: _Animator(nullptr)
		, _Level(0)
		, _Hungry(false)
		, _Behavior(eBehavior::Swim)
	{
	}
	GuppyAnimationCntrl::~GuppyAnimationCntrl()
	{
	}
	void GuppyAnimationCntrl::Initialize()
	{
		_Animator = GetOwner()->GetComponent<Animator>();
	}
	void GuppyAnimationCntrl::Update()
	{
		_Level = GetOwner()->GetComponent<GuppyScript>()->GetLevel();
		_Hungry = GetOwner()->GetComponent<GuppyScript>()->IsHungry();
		_Behavior = GetOwner()->GetComponent<GuppyScript>()->GetBehavior();
	}
	void GuppyAnimationCntrl::LateUpdate()
	{
	}
	void GuppyAnimationCntrl::Render()
	{
	}
	void GuppyAnimationCntrl::Play()
	{
		_Level = GetOwner()->GetComponent<GuppyScript>()->GetLevel();
		_Hungry = GetOwner()->GetComponent<GuppyScript>()->IsHungry();
		_Behavior = GetOwner()->GetComponent<GuppyScript>()->GetBehavior();
		switch (_Behavior)
		{
		case eBehavior::Swim:
			if (_Hungry)
				HungrySwim();
			else
				Swim();
			break;
		case eBehavior::Turn:
			if (_Hungry)
				HungryTurn();
			else
				Turn();
			break;
		case eBehavior::Eat:
			break;
		case eBehavior::End:
			break;
		default:
			break;
		}
	}
	void GuppyAnimationCntrl::Swim()
	{
		switch (_Level)
		{
		case 1:
			_Animator->PlayAnimation(L"Swim_Small", true);
			break;
		case 2:
			_Animator->PlayAnimation(L"Swim_Middle", true);
			break;
		case 3:
			_Animator->PlayAnimation(L"Swim_Large", true);
			break;
		default:
			break;
		}
	}
	void GuppyAnimationCntrl::Turn()
	{
		switch (_Level)
		{
		case 1:
			if (GetOwner()->GetComponent<GuppyScript>()->GetDir() == eDir::Right)
			{
				_Animator->PlayAnimation(L"Turn_Small_Revers", true);
			}
			else
				_Animator->PlayAnimation(L"Turn_Small", true);
			break;
		case 2:
			_Animator->PlayAnimation(L"Turn_Middle", true);
			break;
		case 3:
			_Animator->PlayAnimation(L"Turn_Large", true);
			break;
		default:
			break;
		}
	}
	void GuppyAnimationCntrl::HungrySwim()
	{
		switch (_Level)
		{
		case 1:
			_Animator->PlayAnimation(L"Hungry_Swim_Small", true);
			break;
		case 2:
			_Animator->PlayAnimation(L"Hungry_Swim_Middle", true);
			break;
		case 3:
			_Animator->PlayAnimation(L"Hungry_Swim_Large", true);
			break;
		default:
			break;
		}
	}
	void GuppyAnimationCntrl::HungryTurn()
	{
		switch (_Level)
		{
		case 1:
			_Animator->PlayAnimation(L"Hungry_Turn_Small", false);
			break;
		case 2:
			_Animator->PlayAnimation(L"Hungry_Turn_Middle", false);
			break;
		case 3:
			_Animator->PlayAnimation(L"Hungry_Turn_Large", false);
			break;
		default:
			break;
		}
	}
}