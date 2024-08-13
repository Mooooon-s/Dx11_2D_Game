#include "MnUltravore.h"
#include "MnUltravoreRender.h"
#include "MnUltravoreBehaviorTree.h"
#include "MnTime.h"

namespace Mn
{
	Ultravore::Ultravore()
	{
	}
	Ultravore::~Ultravore()
	{
	}
	void Ultravore::Initialize()
	{
		UltravoreRender* UVR = AddComponent<UltravoreRender>();
		UltravoreBehaviorTree* UVBT = AddComponent<UltravoreBehaviorTree>();
		GameObject::Initialize();
	}
	void Ultravore::Update()
	{
		if (_Flag != 2)
			DropIntoTank();
		else
			GameObject::Update();
	}
	void Ultravore::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Ultravore::Render()
	{
		GameObject::Render();
	}
	void Ultravore::OnClick(Vector3 pos)
	{
	}
	void Ultravore::DropIntoTank()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->Position();
		if (pos.y >= 0.6f && _Flag == 0)
		{
			pos.y -= 1.5 * Time::DeltaTime();
			tr->Position(pos);
		}
		else if (pos.y <= 0.6f && _Flag == 0) {
			_Flag = 1;
			Resources::Find<Mn::AudioClip>(L"Splash")->Play();
		}

		if (pos.y <= 0.8f && _Flag == 1)
		{
			pos.x += -0.5 * Time::DeltaTime();
			pos.y += 0.5 * Time::DeltaTime();
			tr->Position(pos);
		}
		else if (pos.y >= 0.8f && _Flag == 1)
			_Flag = 2;
	}
}
