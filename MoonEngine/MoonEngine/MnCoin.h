#pragma once
#include "MnGameObject.h"
#include "MnAudioClip.h"
#include "MnResources.h"

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
		virtual void OnClick(Vector3 pos) override;

		void SetLevel(float level) { _Level = level; }
	private:
		float _Speed;
		float _Time;
		float _Level;
		UINT  _Price;
	};

}