#pragma once
#include "MnComputeShader.h"
#include "MnStructedBuffer.h"

namespace Mn::graphics
{

	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetParticleBuffer(StructedBuffer* particleBuffer);
		void SetSharedBuffer(StructedBuffer* sharedBuffer) { _SharedBuffer = sharedBuffer; }


	private:
		StructedBuffer* _ParticleBuffer;
		StructedBuffer* _SharedBuffer;
	};

}