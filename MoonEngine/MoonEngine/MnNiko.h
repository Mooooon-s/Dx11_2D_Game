#pragma once
#include "../Engine_SOURCE/MnGameObject.h"

namespace Mn
{
	class Niko : public GameObject
	{
	public:
		Niko();
		~Niko();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Click() override;
	private:
	};
}
