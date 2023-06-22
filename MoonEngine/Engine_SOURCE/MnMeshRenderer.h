#pragma once
#include "MnComponent.h"
#include "MnMesh.h"
#include "MnMaterial.h"

namespace Mn
{
	class MeshRenderer : public Component
	{
	private:
		Mesh* _Mesh;
		Material* _Material;
	public:
		MeshRenderer();
		~MeshRenderer();
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:
		void SetMesh(Mesh* mesh) { _Mesh = mesh; }
		void SetMaterial(Material* material) { _Material = material; }
	};

}
