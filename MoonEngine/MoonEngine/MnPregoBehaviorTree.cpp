#include "MnPregoBehaviorTree.h"
#include "MnRootNode.h"
#include "MnPregoAnimationCntrl.h"
#include "MnMeshRenderer.h"
#include "MnGameObject.h"

#include "MnSequence.h"
#include "MnSelector.h"
#include "MnInverter.h"
#include "MnSucceeder.h"

#include "MnIsPregMent.h"
#include "MnIsBirth.h"
#include "MnBirthGuppy.h"


#include "MnIsTurn.h"
#include "MnFishTurn.h"
#include "MnMove.h"

namespace Mn
{
	PregoBehaviorTree::PregoBehaviorTree()
		: _BlackBoard(nullptr)
		, _Root(nullptr)
	{
	}
	PregoBehaviorTree::~PregoBehaviorTree()
	{
	}
	void PregoBehaviorTree::Initialize()
	{
		_BlackBoard = std::make_shared<BlackBoard>();

		_BlackBoard->AddData<GameObject>(L"Owner", GetOwner());

		PregoAnimationCntrl* PAC = new PregoAnimationCntrl(_BlackBoard.get());
		_BlackBoard->AddData<PregoAnimationCntrl>(L"AnimaCntrl", PAC);

		_BlackBoard->MakeData<eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", eDir::Left);

		_BlackBoard->MakeData<float>(L"MoveSpeed");
		_BlackBoard->SetData(L"MoveSpeed", 0.2f);

		_BlackBoard->MakeData<eBehavior>(L"Behavior");
		_BlackBoard->SetData(L"Behavior", eBehavior::Swim);

		_BlackBoard->MakeData<eFishType>(L"Fish_Type");
		_BlackBoard->SetData(L"Fish_Type", eFishType::Prego);

		_BlackBoard->MakeData<eFishState>(L"Fish_State");
		_BlackBoard->SetData(L"Fish_State", eFishState::Full);

		_BlackBoard->MakeData<bool>(L"PregMent");
		_BlackBoard->SetData(L"PregMent", false);

		_BlackBoard->MakeData<float>(L"PregMentTime");
		_BlackBoard->SetData(L"PregMentTime", 0.0f);

		_BlackBoard->MakeData<float>(L"BirthTime");
		_BlackBoard->SetData(L"BirthTime", 0.0f);


		_Root = new RootNode(_BlackBoard.get());
		_Root->SetTimer();

		Selector* selector = _Root->setChild<Selector>();

		Sequence* pregMentSequence = selector->AddChild<Sequence>();
		IsPregMent* ispregment = pregMentSequence->AddChild<IsPregMent>();
		IsBirth* isbirth = pregMentSequence->AddChild<IsBirth>();

		Sequence* swimSequence = selector->AddChild<Sequence>();
		Succeeder* turnSucceder = swimSequence->AddChild<Succeeder>();
		Sequence* turnSequence = turnSucceder->SetChild<Sequence>();
		IsTurn* isturn = turnSequence->AddChild<IsTurn>();
		FishTurn* fishTurn = turnSequence->AddChild<FishTurn>();

		PregoAnimationCntrl* PACnode = swimSequence->AddChild<PregoAnimationCntrl>();
		Move* swim = swimSequence->AddChild<Move>();
	}
	void PregoBehaviorTree::Update()
	{
		_Root->Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);
	}
	void PregoBehaviorTree::LateUpdate()
	{
	}
	void PregoBehaviorTree::Render()
	{
	}
}