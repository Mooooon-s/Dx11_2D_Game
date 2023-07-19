#pragma once
#include "MnBackGround.h"

namespace Mn
{

	class CaveWall : public BackGround
	{
	private:

	public:
		CaveWall();
		~CaveWall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}