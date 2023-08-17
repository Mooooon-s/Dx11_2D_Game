#include "MnMesh.h"
#include "MnRenderer.h"

namespace Mn
{
	using namespace renderer;
	Mesh::Mesh()
		: Resource(enums::eResourceType::Mesh)
		, _VertexBuffer(nullptr)
		, _IdxBuffer(nullptr)
		, _VertexDesc{}
		, _IndexDesc{}
		,_IndexCount(0)
	{
	}
	Mesh::~Mesh()
	{
	}
	HRESULT Mesh::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	bool Mesh::CreateVertexBuffer(void* data, UINT Count)
	{
		_VertexDesc.ByteWidth = sizeof(renderer::Vertex) * Count;
		_VertexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		_VertexDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		_VertexDesc.CPUAccessFlags = 0; // NONE

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = data;
		
		if (!GetDevice()->CreateBuffer(&_VertexDesc, &sub, _VertexBuffer.GetAddressOf()))
			return false;

		return true;
	}
	bool Mesh::CreateIndexBuffer(void* data, UINT Count)
	{
		_IndexCount = Count;
		_IndexDesc.ByteWidth = sizeof(UINT) * Count;
		_IndexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		_IndexDesc.Usage = D3D11_USAGE_DEFAULT;
		_IndexDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = data;
		if (!GetDevice()->CreateBuffer(&_IndexDesc, &sub, _IdxBuffer.GetAddressOf()))
			return false;
		return true;
	}
	void Mesh::BindBuffer()
	{
		UINT Stride = sizeof(renderer::Vertex);
		UINT offset = 0;

		GetDevice()->BindVertexBuffer(0, _VertexBuffer.GetAddressOf(), &Stride, &offset);
		GetDevice()->BindIndexBuffer(_IdxBuffer.Get(),DXGI_FORMAT_R32_UINT,0);
	}
	void Mesh::Render()
	{
		GetDevice()->DrawIndexed(_IndexCount, 0, 0);
	}
	void Mesh::RenderInstanced(UINT startIndexLocation)
	{
		GetDevice()->DrawIndexedInstanced(_IndexCount, startIndexLocation, 0, 0, 0);
	}
}