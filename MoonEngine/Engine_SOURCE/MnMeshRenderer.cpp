#include "MnMeshRenderer.h"
#include "MnGameObject.h"
#include "MnTransform.h"
#include "MnRenderer.h"
#include "MnAnimator.h"

namespace Mn
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::Meshrenderer)
		, _Mesh(nullptr)
		, _Material(nullptr)
		, _FlipX(0)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::LateUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Flip];
		renderer::FlipCB data = {};
		data.FlipX = _FlipX;
		cb->setData(&data);
		cb->Bind(eShaderStage::PS);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->BindConstantBuffer();

		_Mesh->BindBuffer();
		_Material->Binds();


		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
		{
			animator->Binds();
		}

		_Mesh->Render();
		
		_Material->Clear();
	}
	Vector2 MeshRenderer::CalculateRatio()
	{
		Material* mat = GetOwner()->GetComponent<Material>();
		return mat->CalcurateRatio();
	}
}