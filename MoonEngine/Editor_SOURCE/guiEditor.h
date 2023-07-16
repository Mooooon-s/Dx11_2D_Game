#pragma once
#include "../Engine_SOURCE/CommonInclude.h"
#include "../Engine_SOURCE/MoonEngine.h"
#include "../Engine_SOURCE/MnGraphics.h"

#include "guiWidget.h"
#include "guiEditorobject.h"
#include "guiDebugObject.h"

namespace gui
{

	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const Mn::graphics::DebugMesh& mesh);

	private:
		static std::vector<Widget*> _Widgets;
		static std::vector<EditorObject*> _EditorObjects;
		static std::vector<DebugObject*> _DebugOjbects;
	};

}
