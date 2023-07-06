#pragma once
#include "MnGameObject.h"

namespace Mn
{
	using namespace enums;
	class UI : public GameObject
	{
	private:
		eUIType _UIType;
	public:
		UI();
		virtual ~UI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}
