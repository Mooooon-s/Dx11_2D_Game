#include "MnStinkyBehaviorTree.h"
#include "MnRootNode.h"
#include "MnSequence.h"
#include "MnRepeatUntilFail.h"

#include "MnSelector.h"
#include "MnInverter.h"
#include "MnFindBoss.h"
#include "MnStinkyHide.h"

#include "MnComeOut.h"
#include "MnFindCoin.h"
#include "MnMove2Coin.h"

#include "MnGameObject.h"

namespace Mn
{
	StinkyBehaviorTree::StinkyBehaviorTree()
		: _BlackBoard(nullptr)
		, _Root(nullptr)
	{
	}
	StinkyBehaviorTree::~StinkyBehaviorTree()
	{
	}
	void StinkyBehaviorTree::Initialize()
	{
		_BlackBoard = new BlackBoard();
		_BlackBoard->AddData(L"Owner", GetOwner());

		Vector3 distance = Vector3::Zero;
		_BlackBoard->MakeData<Vector3>(L"Nearest_Distance");
		_BlackBoard->SetData(L"Nearest_Distance", distance);

		enums::eDir dir = enums::eDir::Left;
		_BlackBoard->MakeData<enums::eDir>(L"Dir");
		_BlackBoard->SetData(L"Dir", dir);

		bool hide = false;
		_BlackBoard->MakeData<bool>(L"Hiding");
		_BlackBoard->SetData(L"Hiding", hide);


		_Root = new RootNode(_BlackBoard);
		_Root->SetTimer();

		Sequence* sequence = _Root->setChild<Sequence>();
		Inverter* inverter = sequence->AddChild<Inverter>();
		Sequence* findsequence = inverter->SetChild<Sequence>();
		FindBoss* finsBoss = findsequence->AddChild<FindBoss>();
		StinkyHide* stinkyHide = findsequence->AddChild<StinkyHide>();


		ComeOut* comeOut = sequence->AddChild<ComeOut>();
		FindCoin* findCoin = sequence->AddChild<FindCoin>();
		Move2Coin* move2coin = sequence->AddChild<Move2Coin>();
	}
	void StinkyBehaviorTree::Update()
	{
		_Root->Run();
	}
	void StinkyBehaviorTree::LateUpdate()
	{
	}
	void StinkyBehaviorTree::Render()
	{
	}
	void StinkyBehaviorTree::OnCollisionEnter(Collider2D* other)
	{
		other->GetOwner()->OnClick(Vector3::Zero);
	}
}