#include "MnParticleShader.h"
#include "MnConstantBuffer.h"
#include "MnRenderer.h"
#include "MnTime.h"


namespace Mn::graphics
{
	ParticleShader::ParticleShader()
		: ComputeShader(128, 1, 1)
		, _ParticleBuffer(nullptr)
	{
	}
	ParticleShader::~ParticleShader()
	{
	}
	void ParticleShader::Binds()
	{
		_ParticleBuffer->BindUAV(0);
		_SharedBuffer->BindUAV(1);

		_GroupX = _ParticleBuffer->GetStride() / _ThreadGroupCountX + 1;
		_GroupY = 1;
		_GroupZ = 1;
	}
	void ParticleShader::Clear()
	{
		_ParticleBuffer->Clear();
		_SharedBuffer->Clear();
	}
	void ParticleShader::SetParticleBuffer(StructedBuffer* particleBuffer)
	{
		_ParticleBuffer = particleBuffer;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Particle];

		static float elapsedTime = 0.0f;
		elapsedTime += Time::DeltaTime();

		renderer::ParticleCB data = {};
		data.elementCount = _ParticleBuffer->GetStride();
		data.elpasedTime = elapsedTime;
		data.deltaTime = Time::DeltaTime();

		cb->setData(&data);
		cb->Bind(eShaderStage::CS);
	}
}