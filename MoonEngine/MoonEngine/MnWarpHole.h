#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class WarpHole : public GameObject
	{
	public:
		WarpHole();
		~WarpHole();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	public:
		void BossType(eBossType type) { _Type = type; }

	public:
		void SpawnBoss(Vector3 pos);
	private:
		eBossType _Type;
		float _Time;
		bool _Flag;
	};

}