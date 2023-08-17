#pragma once
#include "MnMeshRenderer.h"
#include "MnStructedBuffer.h"
#include "MnParticleShader.h"

namespace Mn
{
	class ParticleSystem : public MeshRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		graphics::StructedBuffer* _Buffer;
		graphics::StructedBuffer* _SharedBuffer;
		std::shared_ptr<ParticleShader> _CS;

		UINT    _Count;
		Vector4 _StartSize;
		Vector4 _EndSize;
		Vector4 _StartColor;
		Vector4 _EndColor;
		float   _LifeTime;
		float	_Frequency;

		float _Time;
	};
}
