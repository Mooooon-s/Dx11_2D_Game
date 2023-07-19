#pragma once
#pragma once
#include "../Engine_SOURCE/MnUI.h"
#include "../Engine_SOURCE/MnScene.h"

namespace Mn
{
	class HpFrame : public UI
	{
	private:
		Scene* _Scene;
	public:
		HpFrame(Scene* scene);
		~HpFrame();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}