#pragma once
#include "MnMonster.h"

namespace Mn
{

	class Pumpkin : public Monster
	{
	private:
	public:
		Pumpkin();
		~Pumpkin();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}