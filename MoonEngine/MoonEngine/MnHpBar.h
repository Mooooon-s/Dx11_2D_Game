#pragma once
#include "../Engine_SOURCE/MnUI.h"
#include "../Engine_SOURCE/MnScene.h"

namespace Mn
{
	class HpBar : public UI
	{
	private:
		Scene* _Scene;
	public:
		HpBar(Scene* scene);
		~HpBar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}