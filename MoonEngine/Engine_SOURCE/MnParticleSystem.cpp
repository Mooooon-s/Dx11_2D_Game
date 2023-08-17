#include "MnParticleSystem.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnGameObject.h"
#include "MnTime.h"

namespace Mn
{
	ParticleSystem::ParticleSystem()
		: _Count(0)
		, _StartSize(Vector4::One)
		, _EndSize(Vector4::One)
		, _StartColor(Vector4::Zero)
		, _EndColor(Vector4::Zero)
		, _LifeTime(0.0f)
		, _Time(0.0f)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		_CS = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			Vector4 pos = Vector4::Zero;
			/*pos.x += rand() % 20;
			pos.y += rand() % 10;

			int sign = rand() % 2;
			if (sign == 0)
				pos.x *= -1.0f;
			sign = rand() % 2;
			if (sign == 0)
				pos.y *= -1.0f;*/

			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)1000))
					, sinf((float)i * (XM_2PI / 100.f))
					, 0.0f, 1.0f);


			particles[i].position = pos;
			particles[i].speed = 1.0f;
			particles[i].active = 0;
		}

		_Buffer = new graphics::StructedBuffer();
		_Buffer->Create(sizeof(Particle), 1000, eViewType::UAV,particles);
		_SharedBuffer = new graphics::StructedBuffer();
		_SharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);

		//ParticleShared shareData = {};
		//shareData.sharedActiveCount = 1000;
		//_SharedBuffer->SetData(&shareData, 1);
		//_Buffer->SetData(particles, 1000);
	}
	ParticleSystem::~ParticleSystem()
	{
	}
	void ParticleSystem::Initialize()
	{
	}
	void ParticleSystem::Update()
	{
	}
	void ParticleSystem::LateUpdate()
	{
		float AliveTime = 1.0f / 1.0f;
		_Time += Time::DeltaTime();

		if (_Time > AliveTime)
		{
			float f = (_Time / AliveTime);
			UINT AliveCount = (UINT)f;
			_Time = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = 2;
			_SharedBuffer->SetData(&shareData, 1);
		}
		else
		{
			ParticleShared shareData = {};
			shareData.sharedActiveCount = 0;
			_SharedBuffer->SetData(&shareData, 1);
		}


		_CS->SetParticleBuffer(_Buffer);
		_CS->SetSharedBuffer(_SharedBuffer);
		_CS->OnExcute();
	}
	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		_Buffer->BindSRV(eShaderStage::VS, 15);
		_Buffer->BindSRV(eShaderStage::GS, 15);
		_Buffer->BindSRV(eShaderStage::PS, 15);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);

		_Buffer->Clear();
	}
}