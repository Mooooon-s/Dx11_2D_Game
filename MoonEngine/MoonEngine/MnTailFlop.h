#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class TailFlop : public GameObject
	{
	public:
		TailFlop();
		~TailFlop();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:

	};
}
