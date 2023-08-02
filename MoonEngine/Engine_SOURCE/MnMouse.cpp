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
	}
	void Mouse::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Mouse::Render()
	{
	}
}