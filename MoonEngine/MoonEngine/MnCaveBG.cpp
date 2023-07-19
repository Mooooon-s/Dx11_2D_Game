#include "MnCaveBG.h"
#include "MnObject.h"
#include "MnCaveWall.h"
#include "MnCavePillar.h"
#include "MnCaveRock.h"

namespace Mn
{
	CaveBG::CaveBG(Scene* scene)
		: _Scene(scene)
	{
	}
	CaveBG::~CaveBG()
	{
	}
	void CaveBG::Initialize()
	{
		CaveWall* caveWall = object::Instantiate<CaveWall>(eLayerType::BackGround,_Scene);
		caveWall->Initialize();
		CavePillar* cavePillar = object::Instantiate<CavePillar>(eLayerType::BackGround, _Scene);
		cavePillar->Initialize();
		CaveRock* caveRock = object::Instantiate<CaveRock>(eLayerType::BackGround, _Scene);
		caveRock->Initialize();
	}
}