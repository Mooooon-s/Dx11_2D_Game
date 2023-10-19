#include "MnParticleSystem.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnGameObject.h"
#include "MnTime.h"

#include <random>

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
		, _Pos(Vector4::Zero)
		, _Particles{}
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);
		_CS = Resources::Find<ParticleShader>(L"ParticleSystemShader");
		for (size_t i = 0; i < 1000; i++)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0.0, 2.0);
			std::uniform_real_distribution<> ac(0.0, 1.0);
			std::uniform_real_distribution<> t(0.0, 4.0);

			_Particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)1000))
					, sinf((float)i * (XM_2PI / 100.f))
					, 0.0f, 1.0f);

			_Particles[i].position = _Pos;
			_Particles[i].speed = (float)dis(gen);
			_Particles[i].active = 0;

			_Particles[i].endTime= (float)t(gen);
			_Particles[i].time = 0;
		}

		_Buffer = new graphics::StructedBuffer();
		_Buffer->Create(sizeof(Particle), 1000, eViewType::UAV, _Particles,true);
		_SharedBuffer = new graphics::StructedBuffer();
		_SharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);
	}
	ParticleSystem::ParticleSystem(Vector3 position)
		: _Count(0)
		, _StartSize(Vector4::One)
		, _EndSize(Vector4::One)
		, _StartColor(Vector4::Zero)
		, _EndColor(Vector4::Zero)
		, _LifeTime(0.0f)
		, _Time(0.0f)
		, _Pos(Vector4(position.x, position.y, position.z,0.0f))
		, _Particles{}
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);
		_CS = Resources::Find<ParticleShader>(L"ParticleSystemShader");
		for (size_t i = 0; i < 1000; i++)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0.0, 2.0);
			std::uniform_real_distribution<> ac(0.0, 1.0);
			std::uniform_real_distribution<> t(0.0, 4.0);

			//_Pos = Vector4(position.x, position.y, position.z,0.0f);

			_Particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)1000))
					, sinf((float)i * (XM_2PI / 100.f))
					, 0.0f, 1.0f);

			_Particles[i].position = _Pos;
			_Particles[i].speed = (float)dis(gen);
			_Particles[i].active = 0;

			_Particles[i].endTime = (float)t(gen);
			_Particles[i].time = 0;
		}

		_Buffer = new graphics::StructedBuffer();
		_Buffer->Create(sizeof(Particle), 1000, eViewType::UAV, _Particles,true);
		_SharedBuffer = new graphics::StructedBuffer();
		_SharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);
		int a = 0;
	}
	ParticleSystem::~ParticleSystem()
	{
		delete _Buffer;
		delete _SharedBuffer;
	}
	void ParticleSystem::Initialize()
	{
	}
	void ParticleSystem::Update()
	{
	
	}
	void ParticleSystem::LateUpdate()
	{

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0.0, 10.0);

		float AliveTime = 1.0f / 1.0f;
		_Time += Time::DeltaTime();

		if (_Time > AliveTime)
		{
			//Transform* tr = GetOwner()->GetComponent<Transform>();
			//Vector3 pos = tr->Position();
			//_Pos = Vector4(pos.x, pos.y, pos.z, 0.0f);


			float f = (_Time / AliveTime);
			UINT AliveCount = (UINT)f;
			_Time = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = (UINT)dis(gen);
			shareData.position = _Pos;
			_SharedBuffer->SetData(&shareData, 1);
		}
		else
		{
			ParticleShared shareData = {};
			shareData.sharedActiveCount = 0;
			shareData.position = _Pos;
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
		GetMesh()->BindBuffer();
		GetMesh()->RenderInstanced(1000);
		_Buffer->Clear();
	}
}