#pragma once
#include "MnComponent.h"
#include "MnGraphics.h"

namespace Mn
{
	using namespace graphics;
	class Light : public Component
	{
	public:
		Light();
		~Light();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	public:
		LightAttribute GetAttribute() { return _Attribute; }
		void SetType(eLightType rype) { _Attribute.type = rype; }
		void SetRadius(float radius) { _Attribute.radius = radius; }
		void SetAngle(float angle) { _Attribute.angle = angle; }
		void SetColor(Vector4 color) { _Attribute.color = color; }
		Vector4 GetColor() { return _Attribute.color; }
		eLightType GetType() { return _Attribute.type; }
		float GetRadius() { return _Attribute.radius; }
		float GetAngle() { return _Attribute.angle; }
	private:
		LightAttribute _Attribute;
	};

}