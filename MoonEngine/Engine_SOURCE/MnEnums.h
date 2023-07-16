#pragma once
namespace Mn::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Collider2D,
		Particle,
		Meshrenderer,
		Script,
		Camera,
		End,
	};

	enum class eLayerType
	{
		Grid,
		Player,
		Monster,
		BackGround,
		Water,
		UI,
		End=16,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		End,
	};

	enum class eUIType
	{
		State,
		Skill,
		Menu,
		end,
	};

	enum class eDir
	{
		Left,
		Right,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};
}