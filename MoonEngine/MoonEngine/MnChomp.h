#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Chomp : public GameObject
	{
	public:
		Chomp();
		~Chomp();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
	};
}
