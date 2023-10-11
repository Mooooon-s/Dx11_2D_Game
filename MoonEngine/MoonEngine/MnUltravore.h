#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Ultravore : public GameObject
	{
	public:
		Ultravore();
		~Ultravore();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void OnClick(Vector3 pos) override;
	public:
		void DropIntoTank();

		void SetFlag(int flag) { _Flag = flag; }
	private:
		int _Flag;
	};
}
