#pragma once
#include "MnComponent.h"
#include "MnMesh.h"
#include "MnMaterial.h"

namespace Mn
{
	class MeshRenderer : public Component
	{
	private:
		std::shared_ptr<Mesh>		_Mesh;
		std::shared_ptr<Material>	_Material;
		UINT _FlipX;
		float _Alpha;
	public:
		MeshRenderer();
		~MeshRenderer();
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		Vector2 CalculateRatio();

	public:
		void SetMesh(std::shared_ptr<Mesh> mesh) { _Mesh = mesh; }
		void SetMaterial(std::shared_ptr<Material> material) { _Material = material; }
		std::shared_ptr<Material> GetMaterial() { return _Material; }
		std::shared_ptr<Mesh> GetMesh() { return _Mesh; }
		void FlipX(UINT X) { _FlipX = X; }
		void AlphaValue(float alpha) { _Alpha = alpha; }
	};

}
