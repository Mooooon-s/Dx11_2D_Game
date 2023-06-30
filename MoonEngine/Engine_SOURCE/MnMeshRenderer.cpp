#include "MnMeshRenderer.h"
#include "MnGameObject.h"
#include "MnTransform.h"
#include "MnRenderer.h"
#include "MnWaterScript.h"

namespace Mn
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::Meshrenderer)
		, _Mesh(nullptr)
		, _Material(nullptr)
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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->BindConstantBuffer();

		_Mesh->BindBuffer();
		_Material->Binds();
		_Mesh->Render();
		
		_Material->Clear();
	}
}