#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Character : public GameObject
	{
	public:
		enum class eDir
		{
			Left,
			Right,
		};
	private:
		float _Hp;
	public:
		Character();
		virtual ~Character();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	};
}
