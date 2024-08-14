#include "MnEggCrackEvent.h"
#include "MnResources.h"
#include "MnEggCrackButton.h"
#include "MnObject.h"
#include "MnCreateIcon.h"
#include "MnNikoIcon.h"
#include "MnEggCrack.h"
#include "MnFontWrapper.h"
#include "MnSoundManager.h"

#define ICON_POSITION Vector3(0.0f, 0.85f, -9.1f)
#define BUTTONPOSITION Vector3(0.0f, -1.65f, -9.1f)

namespace Mn
{
	EggCrackEvent::EggCrackEvent()
	{
	}
	EggCrackEvent::~EggCrackEvent()
	{
	}
	void EggCrackEvent::Initialize()
	{
		SetName(L"EggCrackPanel");
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"EggCrackPanel"));
		Vector2 ratio = mr->GetMaterial()->GetTexture()->CalculateRatio();
		GetComponent<Transform>()->Scale(Vector3(ratio.x * 3.6, ratio.y * 3.6, 1.0f));

		EggCrackButton* ECB = object::Instantiate<EggCrackButton>(BUTTONPOSITION, eLayerType::UI);
		ECB->SetIcon(_Icon);
		ECB->SetEvent(this);
		ECB->Initialize();
		EggCrack* eggcrack = object::Instantiate<EggCrack>(ICON_POSITION, eLayerType::UI);
		eggcrack->SetIcon(_Icon);
		eggcrack->SetEvent(this);
		eggcrack->Initialize();
		_EventObject.push_back(ECB);

		GameObject::Initialize();
	}
	void EggCrackEvent::Update()
	{
		Coment();
		GameObject::Update();
	}
	void EggCrackEvent::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void EggCrackEvent::Render()
	{
		GameObject::Render();
	}
	void EggCrackEvent::FontRender()
	{
		FontWrapper::DrawFont(_szString, 300, 360, 30, FONT_RGBA(255, 255, 255, 255));
		GameObject::FontRender();
	}
	void EggCrackEvent::OnClick()
	{
		for (auto obj : _EventObject)
		{
			obj->State(GameObject::eState::Dead);
		}
		this->State(GameObject::eState::Dead);
		MnSoundManager::SoundStop(L"Stage_Award_Music");
		MnSoundManager::SetVolum(L"Stage_BackGround_Music", 0.3f);
	}
	void EggCrackEvent::Coment()
	{
		switch (_Icon)
		{
		case Mn::enums::eIcon::Niko:
			_str = L"\t  Niko\nCreate Pearl every min Time\n";
			break;
		case Mn::enums::eIcon::Stinky:
			_str = L"\t  Stinky\nPickup coin instead you\n";
			break;
		case Mn::enums::eIcon::Zorf:
			_str = L"\t  Zorf\nIf your guppies are hungry,\n make them food.\n";
			break;
		case Mn::enums::eIcon::Prego:
			_str = L"\t  Prego\nCreate one guppy every min\n Time \n";
			break;
		case Mn::enums::eIcon::Amp:
			_str = L"\t  Amp\nElectrocute the guppies\n to create diamonds.\n";
			break;
		case Mn::enums::eIcon::End:
			break;
		default:
			break;
		}
		swprintf_s(_szString, 100, L"%ls", _str.c_str());
	}
}