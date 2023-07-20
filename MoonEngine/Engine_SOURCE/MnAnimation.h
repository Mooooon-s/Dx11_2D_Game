#pragma once
#include "MoonEngine.h"
#include "MnResource.h"
#include "MnTexture.h"

namespace Mn
{
	using namespace graphics;
	using namespace math;

	class Animator;
	class Texture;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			float duration;

			Sprite()
				:leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};


		Animation();
		~Animation();

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };
		void Update();
		void LateUpdate();
		void Render();

		void Create(std::wstring name, std::shared_ptr<graphics::Texture> atlas, Vector2 leftTop, Vector2 size, UINT columLength, Vector2 offset = Vector2::Zero, float duration = 0.0f);
		void Binds();
		void Reset();

	private:
		std::shared_ptr<graphics::Texture> _Atlas;
		std::vector<Sprite> _Sprites;
		class Animator* _Animator;
		int _Index;
		float _Time;
		bool _Complete;
	};
}