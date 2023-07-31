#pragma once
#include "../Engine_SOURCE/MnBtNode.h"
#include "../Engine_SOURCE/MnBlackBoard.h"
namespace Mn
{

	class IsTurn : public Node
	{
	public:
		IsTurn();
		IsTurn(BlackBoard* board);
	public:
		int RandomInt();
		int Generate();
		virtual enums::eBTState Run() override;
	private:
		BlackBoard* _BlackBoard;
	};

}