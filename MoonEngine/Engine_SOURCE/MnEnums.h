#pragma once
namespace Mn::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
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
		End,
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
}