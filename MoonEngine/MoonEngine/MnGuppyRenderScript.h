#pragma once
#include "MnScript.h"

namespace Mn
{
	class Texture;
	class GuppyRender : public Script
	{

	public:
		GuppyRender();
		~GuppyRender();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		std::shared_ptr<Mn::graphics::Texture> atlases[2];
		eFishState _PreState;
	};

}