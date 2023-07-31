#include "MnBlackBoard.h"
namespace Mn
{
	BlackBoard::BlackBoard()
		:_BlackBoard{}
		, _RunningNode(nullptr)
	{
	}
	Node** BlackBoard::GetRunningNode()
	{
		if(_RunningNode==nullptr)
			return nullptr;
		return _RunningNode;
	}
	void BlackBoard::ResetRunningNode()
	{
		_RunningNode = nullptr;
	}
}