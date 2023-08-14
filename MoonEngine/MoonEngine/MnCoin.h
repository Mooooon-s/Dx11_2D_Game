#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Coin : public GameObject
	{
	public:
		Coin();
		~Coin();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetLevel(float level) { _Level = level; }
	private:
		float _Speed;
		float _Time;
		float _Level;
	};

}