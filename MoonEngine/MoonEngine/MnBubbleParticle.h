#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class BubbleParticle : public GameObject
	{
	public:
		BubbleParticle();
		~BubbleParticle();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	public:
		void SetTarget(GameObject* target) { _Target = target; }
	private:
		GameObject* _Target;
		class ParticleSystem* _PS;
	};
}
