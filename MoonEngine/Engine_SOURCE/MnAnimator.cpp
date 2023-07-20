#include "MnAnimator.h"

namespace Mn
{
	Animator::Animator()
		:Component(enums::eComponentType::Animator)
	{
	}
	Animator::~Animator()
	{
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
	}
	void Animator::LateUpdate()
	{
	}
	void Animator::Render()
	{
	}
	void Animator::Create(std::wstring name, std::shared_ptr<graphics::Texture> atlas, Vector2 leftTop, Vector2 size, UINT columLength, Vector2 offset, float duration)
	{

	}
}