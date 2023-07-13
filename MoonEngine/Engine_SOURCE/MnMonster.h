#pragma once
#include "MnCharacter.h"

namespace Mn
{

	class Monster : public Character
	{
	private:
	public:
		Monster();
		virtual ~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}