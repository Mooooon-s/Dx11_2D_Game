#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class EggCrackEvent : public GameObject
	{
	public:
		EggCrackEvent();
		~EggCrackEvent();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void FontRender();
		virtual void OnClick();
	public:
		void Coment();
	public:
		void SetIcon(eIcon icon) { _Icon = icon; };
		void AddObj(GameObject* obj) { _EventObject.push_back(obj); }
	private:
		eIcon _Icon;
		wchar_t _szString[100];
		std::wstring _str;
		std::vector<GameObject*> _EventObject;
	};
}
