#include "MnMouse.h"

#include <vector>


#include "MnInput.h"
#include "MnTransform.h"
#include "MnMousePosScript.h"


using namespace Mn::math;
namespace Mn
{
	Mouse::Mouse()
	{
	}
	Mouse::~Mouse()
	{
	}
	void Mouse::Initialize()
	{
		MousePosScript* mps = AddComponent<MousePosScript>();
		mps->UICamera(_Cam);
	}
	void Mouse::Update()
	{
		GameObject::Update();
	}
	void Mouse::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Mouse::Render()
	{
	}
	void Mouse::ScriptFoodLevel()
	{
		MousePosScript* MPS = GetComponent<MousePosScript>();
		MPS->FoodLevel();
	}
	void Mouse::ScriptFoodCount()
	{
		MousePosScript* MPS = GetComponent<MousePosScript>();
		if (MPS->GetFoodCount() < 5)
			MPS->FoodCount();
	}
}