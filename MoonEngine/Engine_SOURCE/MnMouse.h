#pragma once
#include "MnInput.h"
#include "MnGameObject.h"
namespace Mn
{
	using namespace Mn::math;
	class Mouse : public GameObject
	{
	public:
		Mouse();
		~Mouse();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	public:
		void UICamera(GameObject* cam) { _Cam = cam; }
	private:
		GameObject* _Cam;
	};

}