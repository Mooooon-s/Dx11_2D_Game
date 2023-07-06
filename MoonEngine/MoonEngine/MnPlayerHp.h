#pragma once
#include "../Engine_SOURCE/MnUI.h"
#include "../Engine_SOURCE/MnScene.h"

namespace Mn
{
	class PlayerHp : public UI
	{
	private:
		Scene* _Scene;
	public:
		PlayerHp(Scene* scene);
		~PlayerHp();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}
