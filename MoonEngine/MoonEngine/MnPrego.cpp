#include "MnPrego.h"
#include "MnPregoRnder.h"
#include "MnPregoBehaviorTree.h"

namespace Mn
{
	Prego::Prego()
	{
	}
	Prego::~Prego()
	{
	}
	void Prego::Initialize()
	{
		PregoRnder* PR = AddComponent<PregoRnder>();
		PregoBehaviorTree* PBT = AddComponent<PregoBehaviorTree>();
		GameObject::Initialize();
	}
	void Prego::Update()
	{
		GameObject::Update();
	}
	void Prego::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Prego::Render()
	{
		GameObject::Render();
	}
}