#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Coin : public GameObject
	{
	public:
		Coin();
		~Coin();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Click() override;

		void SetLevel(float level) { _Level = level; }
	private:
		float _Speed;
		float _Time;
		float _Level;
	};

}