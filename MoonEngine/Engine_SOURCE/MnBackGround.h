#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class BackGround : public GameObject
	{
	private:

	public:
		BackGround();
		virtual ~BackGround();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}
