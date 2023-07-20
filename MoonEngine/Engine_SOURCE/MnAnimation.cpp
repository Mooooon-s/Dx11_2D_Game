#include "MnAnimation.h"
#include "MnTexture.h"
#include "MnAnimator.h"
#include "MnTime.h"

namespace Mn
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, _Atlas(nullptr)
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
		}

		if (_Sprites.size() <= _Index)
		{
			_Index = _Sprites.size() - 1;
			_Complete = true;
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
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			_Sprites.push_back(sprite);

		}
	}
	void Animation::Binds()
	{
		//TextureBinds
		_Atlas->BindShader(graphics::eShaderStage::PS, 12);

		//AnimationCB


	}
	void Animation::Reset()
	{
		_Time = 0.0f;
		_Complete = false;
		_Index = -1;
	}
}