#pragma once
#include "../Engine_SOURCE/MnGameObject.h"

namespace gui
{

	class EditorObject : public Mn::GameObject
	{
	public:
		EditorObject();
		virtual ~EditorObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}