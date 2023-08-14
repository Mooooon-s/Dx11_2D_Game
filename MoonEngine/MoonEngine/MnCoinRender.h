#pragma once
#include "MnScript.h"

namespace Mn
{
	class CoinRender : public Script
	{
	public:
		CoinRender();
		~CoinRender();
		
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	public:
		void SetLevel(float level) { _Level = (UINT)level; }

	private:
		UINT _Level;
	};

}