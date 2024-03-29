#pragma once
#include "MnGameObject.h"
#include "MnBalrogBehaviorTree.h"

namespace Mn
{
	class Balrog : public GameObject
	{
	public:
		Balrog();
		~Balrog();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void OnClick(Vector3 pos) override;
	private:
		BalrogBehaviorTree* _BHT;
	};
}
