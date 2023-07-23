#pragma once
#include "MnUI.h"
namespace Mn
{

	class TopBar : public UI
	{
	public:
		TopBar();
		~TopBar();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	private:
		std::shared_ptr<Mn::graphics::Texture> _AlphaTex;
	};

}