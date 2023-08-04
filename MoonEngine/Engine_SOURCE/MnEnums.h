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
		Animator,
		End,
	};

	enum class eLayerType
	{
		Grid,
		Fish,
		Monster,
		BackGround,
		Food,
		UI,
		End=16,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
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

	enum class eFishState
	{
		Full,
		Hungry,
		Starving,
		Death,
		End,
	};

	enum class eBehavior
	{
		Swim,
		Turn,
		Eat,
		End,
	};

	enum class eAquarim
	{
		Stage1,
		Stage2,
		Stage3,
		Stage4,
		Stage5,
		Stage6,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};

	enum class eBTState
	{
		SUCCESS,
		FAILURE,
		RUNNING,
	};
}