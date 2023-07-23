#include "MnGuppyAnimationCntrl.h"
#include "MnGameObject.h"
#include "MnGuppyScript.h"
#include "MnMeshRenderer.h"
#include "MnMaterial.h"
#include "MnResources.h"

namespace Mn
{
	GuppyAnimationCntrl::GuppyAnimationCntrl()
	{
	}
	GuppyAnimationCntrl::~GuppyAnimationCntrl()
	{
	}
	void GuppyAnimationCntrl::Initialize()
	{
	}
	void GuppyAnimationCntrl::Update()
	{
		_Behavior = GetOwner()->GetComponent<GuppyScript>()->GetBehavior();
		_Hungry = GetOwner()->GetComponent<GuppyScript>()->IsHungry();
	}
	void GuppyAnimationCntrl::LateUpdate()
	{
	}
	void GuppyAnimationCntrl::Render()
	{
		//std::shared_ptr<Material> mat = GetOwner()->GetComponent<MeshRenderer>()->GetMaterial();
		//switch (_Behavior)
		//{
		//case eBehavior::Swim:
		//	if (_Hungry)
		//	{
		//		mat->TextureBind(Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Sprite_Alpha"), 13);
		//		//mat->SetTexture(Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Sprite"));
		//	}
		//	else
		//	{
		//		mat->TextureBind(Resources::Find<Mn::graphics::Texture>(L"Guppy_Sprite_Alpha"), 13);
		//		//mat->SetTexture(Resources::Find<Mn::graphics::Texture>(L"Guppy_Sprite"));
		//	}
		//	break;
		//case eBehavior::Turn:
		//	if (_Hungry)
		//	{
		//		mat->TextureBind(Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Turn_Sprite_Alpha"), 13);
		//		//mat->SetTexture(Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Turn_Sprite"));
		//	}
		//	else
		//	{
		//		mat->TextureBind(Resources::Find<Mn::graphics::Texture>(L"Guppy_Turn_Sprite_Alpha"), 13);
		//		//mat->SetTexture(Resources::Find<Mn::graphics::Texture>(L"Guppy_Turn_Sprite"));
		//	}
		//	break;
		//case eBehavior::Eat:
		//	if (_Hungry)
		//	{
		//		mat->TextureBind(Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Eat_Sprite_Alpha"), 13);
		//		//mat->SetTexture(Resources::Find<Mn::graphics::Texture>(L"Hungry_Guppy_Eat_Sprite"));
		//	}
		//	else
		//	{
		//		mat->TextureBind(Resources::Find<Mn::graphics::Texture>(L"Guppy_Eat_Sprite_Alpha"), 13);
		//		//mat->SetTexture(Resources::Find<Mn::graphics::Texture>(L"Guppy_Eat_Sprite"));
		//	}
		//	break;
		//default:
		//	break;
		//}
	}
}