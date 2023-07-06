#pragma once
#include "MnGameObject.h"

namespace Mn
{
	using namespace enums;
	class Character : public GameObject
	{
	private:
		eDir	_Dir;
		float	_Hp;
	public:
		Character();
		virtual ~Character();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	public:
		void SetDir(eDir dir) { _Dir = dir; }
		void SetHp(float hp) { _Hp = hp; }

		eDir GetDir() { return _Dir; }
		float GetHp() { return _Hp; }
	};
}
