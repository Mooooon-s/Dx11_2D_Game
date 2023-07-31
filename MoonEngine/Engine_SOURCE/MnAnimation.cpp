#include "MnAnimation.h"
#include "MnTime.h"
#include "MnAnimator.h"
#include "MnRenderer.h"
#include "MnConstantBuffer.h"

namespace Mn
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, _Atlas(nullptr)
		, _AtlasAlpha(nullptr)
		, _Sprites{}
		, _Animator(nullptr)
		, _Index(-1)
		, _Time(0)
		, _Complete(false)
	{
	}
	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
	}
	void Animation::LateUpdate()
	{
		if (_Complete)
			return;

		_Time += Time::DeltaTime();

		if (_Sprites[_Index].duration <= _Time)
		{
			_Index++;
			_Time = 0.0f;


			if (_Sprites.size() <= _Index)
			{
				_Index = _Sprites.size() - 1;
				_Complete = true;
			}
		}

	}
	void Animation::Render()
	{
	}
	void Animation::Create(std::wstring name, std::shared_ptr<graphics::Texture> atlas, Vector2 leftTop, Vector2 size, UINT columLength, Vector2 offset, float duration)
	{
		Key(name);
		_Atlas = atlas;

		float width = (float)atlas->GetImageWidth();
		float height = (float)atlas->GetImageHeight();

		for (size_t i = 0; i < columLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (float)(i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = size.x /width;
			sprite.size.y = size.y /height;
			sprite.offset = offset;
			sprite.atlasSize = Vector2(100.0f / width, 100.0f / height);
			sprite.duration = duration;

			_Sprites.push_back(sprite);

		}
	}
	void Animation::Create(std::wstring name, std::shared_ptr<graphics::Texture> atlas, std::shared_ptr<graphics::Texture> atlasAlpha, Vector2 leftTop, Vector2 size, UINT columLength, Vector2 offset, float duration)
	{
		Key(name);
		_Atlas = atlas;
		_AtlasAlpha = atlasAlpha;

		float width = (float)atlas->GetImageWidth();
		float height = (float)atlas->GetImageHeight();

		for (size_t i = 0; i < columLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (float)(i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = size.x / width;
			sprite.size.y = size.y / height;
			sprite.offset = offset;
			sprite.atlasSize = Vector2(100.0f / width, 100.0f / height);
			sprite.duration = duration;

			_Sprites.push_back(sprite);

		}
	}
	void Animation::CreateReverse(std::wstring name, std::shared_ptr<graphics::Texture> atlas, std::shared_ptr<graphics::Texture> atlasAlpha, Vector2 leftTop, Vector2 size, UINT columLength, Vector2 offset, float duration)
	{
		Key(name);
		_Atlas = atlas;
		_AtlasAlpha = atlasAlpha;

		float width = (float)atlas->GetImageWidth();
		float height = (float)atlas->GetImageHeight();

		for (int i = columLength-1; i >= 0; i--)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (float)(i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = size.x / width;
			sprite.size.y = size.y / height;
			sprite.offset = offset;
			sprite.atlasSize = Vector2(100.0f / width, 100.0f / height);
			sprite.duration = duration;

			_Sprites.push_back(sprite);

		}
	}
	void Animation::Binds()
	{
		//TextureBinds
		_Atlas->BindShader(graphics::eShaderStage::PS, 12);
		if (_AtlasAlpha != nullptr)
		{
			_AtlasAlpha->BindShader(graphics::eShaderStage::PS, 13);
		}
		//AnimationCB
		renderer::AnimatorCB data = {};
		data.SpriteleftTop = _Sprites[_Index].leftTop;
		data.SpriteSize = _Sprites[_Index].size;
		data.SpriteOffset = _Sprites[_Index].offset;
		data.atlasSize = _Sprites[_Index].atlasSize;
		data.animationType = 1;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->setData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);

	}
	void Animation::Reset()
	{
		_Time = 0.0f;
		_Complete = false;
		_Index = 0;
	}
}