#pragma once
#include "../Engine_SOURCE/MnGameObject.h"
#include "../Engine_SOURCE/MnScript.h"

namespace Mn
{
	#define LAYERMAX (UINT)eLayerType::End

	class MousePosScript : public Script
	{
	public:
		MousePosScript();
		MousePosScript(GameObject* cam);

		~MousePosScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	public:
		Vector3 CalculatePos();
		void InterSect(Collider2D* coll);
		void GatherObject();
		GameObject* PrimaryObj();
		void FeedFood();
		void FoodLevel();
		void FoodCount();
		bool MaxFood();
		bool MoneyCheck();
		void PlaySceneMouse();
		void TitleSceneMouse();
	public:
		void UICamera(GameObject* uicamera) { _Cam = uicamera; }
		UINT GetFoodCount() { return _FoodCount; }
	private:
		UINT		_FoodLevel;
		UINT		_FoodCount;
		UINT		_Idx;
		Vector3		_DotPos;
		Vector3		_WinPos;
		Vector3		_UnProjectPos;
		GameObject* _Cam;
		std::vector<GameObject*> _GameObjects;
		std::vector<GameObject*> _InterSectObjs;
		std::bitset<LAYERMAX> _Setting;
	};
}
