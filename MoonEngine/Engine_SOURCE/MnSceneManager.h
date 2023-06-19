#include "MnScene.h"

namespace Mn
{
	class SceneManager
	{
	private:
		static Scene* _ActiveScene;
	public:

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
	};
}
