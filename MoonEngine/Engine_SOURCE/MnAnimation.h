#pragma once
#include "MnResource.h"
#include "MnTexture.h"

namespace Mn
{
	using namespace math;
	using namespace graphics;

	class Animator;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 atlasSize;
			float duration;

			Sprite()
				:leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, atlasSize(Vector2::Zero)
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

		void Create(std::wstring name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f);

		void Create(std::wstring name
			, std::shared_ptr<graphics::Texture> atlas
			, std::shared_ptr<graphics::Texture> atlasAlpha
			, Vector2 leftTop
			, Vector2 size
			, UINT columLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f);

		void CreateReverse(std::wstring name
			, std::shared_ptr<graphics::Texture> atlas
			, std::shared_ptr<graphics::Texture> atlasAlpha
			, Vector2 leftTop
			, Vector2 size
			, UINT columLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f);

		void Binds();
		void Reset();

		bool IsComplete() { return _Complete; }

	private:
		std::shared_ptr<graphics::Texture> _Atlas;
		std::shared_ptr<graphics::Texture> _AtlasAlpha;
		Animator* _Animator;
		std::vector<Sprite> _Sprites;
		int _Index;
		float _Time;
		bool _Complete;
	};
}