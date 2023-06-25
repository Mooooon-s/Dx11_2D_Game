#pragma once
#include "MnCharacter.h"

namespace Mn
{
	class MainCharacter : public Character
	{
	private:

	public:
		MainCharacter();
		~MainCharacter();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

