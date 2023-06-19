#include "MnMeshRenderer.h"
#include "MnGameObject.h"
#include "MnTransform.h"
#include "MnRenderer.h"

namespace Mn
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::Meshrenderer)
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

		renderer::mesh->BindBuffer();
		renderer::shader->binds();
		GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}

}