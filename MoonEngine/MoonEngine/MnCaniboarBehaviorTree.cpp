#include "MnCaniboarBehaviorTree.h"

#include "MnSwim.h"
#include "MnRootNode.h"
#include "MnSequence.h"
#include "MnSelector.h"
#include "MnInverter.h"
#include "MnSucceeder.h"

#include "MnFindSmallGuppy.h"

#include "MnMeshRenderer.h"
#include "MnGameObject.h"
#include "MnCaniBoarAnimatonCntrl.h"
#include "MnIsTurn.h"
#include "MnFishTurn.h"

#include "MnMove.h"

#include "MnHungryStack.h"
#include "MnHungryCheck.h"
#include "MnTurn2Food.h"
#include "MnMove2Guppy.h"


#include "MnIsDeath.h"

#include "MnRepeatUntilFail.h"

namespace Mn
{
	CaniboarBehaviorTree::CaniboarBehaviorTree()
		: _BlackBoard(nullptr)
	{
	}
	CaniboarBehaviorTree::~CaniboarBehaviorTree()
	{
	}
	void CaniboarBehaviorTree::Initialize()
	{
		_BlackBoard = std::make_shared<BlackBoard>();

		CaniBoarAnimatonCntrl* CBAC = new CaniBoarAnimatonCntrl(_BlackBoard.get());
		_BlackBoard->AddData<CaniBoarAnimatonCntrl>(L"AnimaCntrl", CBAC);

		_BlackBoard->AddData<GameObject>(L"Owner", GetOwner());

		_BlackBoard->MakeData<eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", eDir::Left);

		_BlackBoard->MakeData<float>(L"MoveSpeed");
		_BlackBoard->SetData(L"MoveSpeed",0.8f);

		_BlackBoard->MakeData<eFishType>(L"Fish_Type");
		_BlackBoard->SetData(L"Fish_Type", eFishType::CaniBoar);

		_BlackBoard->MakeData<eFishState>(L"Fish_State");
		_BlackBoard->SetData(L"Fish_State", eFishState::Full);

		_BlackBoard->MakeData<eBehavior>(L"Behavior");
		_BlackBoard->SetData(L"Behavior", eBehavior::Swim);

		_BlackBoard->MakeData<int>(L"HungryStack");
		_BlackBoard->SetData(L"HungryStack", 5);

		_BlackBoard->MakeData<Vector3>(L"MoveVector");
		_BlackBoard->SetData(L"MoveVector", Vector3::Zero);

		_BlackBoard->MakeData<UINT>(L"StackFlag");
		_BlackBoard->SetData(L"StackFlag", 1);


		_Root = new RootNode(_BlackBoard.get());
		Selector* rootSelector = _Root->setChild<Selector>();

		//Sequence* deathSequence = rootSelector->AddChild<Sequence>();
		IsDeath* isDeath = rootSelector->AddChild<IsDeath>();
		Sequence* sequence = rootSelector->AddChild<Sequence>();

		

		//Hungry
		Succeeder* hungrySucceder = sequence->AddChild<Succeeder>();
		Sequence* HungrySequence = hungrySucceder->SetChild<Sequence>();


		HungryStack* hungryStack = HungrySequence->AddChild<HungryStack>();
		HungryCheck* hungryCheck = HungrySequence->AddChild<HungryCheck>();

		//Find Food
		RepeatUntilFail* FindFoodUntilFail = HungrySequence->AddChild<RepeatUntilFail>();
		Sequence* findSmallGuppySequence = FindFoodUntilFail->SetChild<Sequence>();
		FindSmallGuppy* FSG = findSmallGuppySequence->AddChild<FindSmallGuppy>();
		Turn2Food* T2F = findSmallGuppySequence->AddChild<Turn2Food>();
		Move2Guppy* M2G = findSmallGuppySequence->AddChild<Move2Guppy>();

		Sequence* swimSequence = sequence->AddChild<Sequence>();

		//turn
		Succeeder* turnSucceder = swimSequence->AddChild<Succeeder>();
		Sequence* turnSequence = turnSucceder->SetChild<Sequence>();
		IsTurn* isturn = turnSequence->AddChild<IsTurn>();
		FishTurn* fishTurn = turnSequence->AddChild<FishTurn>();
		
		//move
		CaniBoarAnimatonCntrl* anima = swimSequence->AddChild<CaniBoarAnimatonCntrl>();
		Move* swim = swimSequence->AddChild<Move>();

		_BlackBoard->AddData<FindSmallGuppy>(L"FindGuppyNode", FSG);

		_Root->SetTimer();
	}
	void CaniboarBehaviorTree::Update()
	{
		_Root->Run();
		MeshRenderer* MR = GetOwner()->GetComponent<MeshRenderer>();
		enums::eDir dir = _BlackBoard->GetDataValue<enums::eDir>(L"Dir");
		if (dir == eDir::Right)
			MR->FlipX(1);
		else
			MR->FlipX(0);
	}
	void CaniboarBehaviorTree::LateUpdate()
	{
	}
	void CaniboarBehaviorTree::Render()
	{
	}
	void CaniboarBehaviorTree::OnCollisionEnter(Collider2D* other)
	{
		eFishState hungrystate = _BlackBoard->GetDataValue<eFishState>(L"Fish_State");
		if (hungrystate != eFishState::Full && other->GetOwner()->GetName() == L"Guppy")
		{
			_BlackBoard->SetData(L"Behavior", enums::eBehavior::Eat);
			_BlackBoard->SetData(L"HungryStack", 5);
			_BlackBoard->SetData(L"Fish_State", eFishState::Full);
			_BlackBoard->ResetRunningNode();
			other->GetOwner()->OnClick();
		}
	}
	void CaniboarBehaviorTree::OnCollisionStay(Collider2D* other)
	{
	}
	void CaniboarBehaviorTree::OnCollisionExit(Collider2D* other)
	{
	}
}