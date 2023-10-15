#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"
namespace Mn
{
	class IsBirth : public Node
	{
	public:
		IsBirth();
		IsBirth(BlackBoard* board);
		~IsBirth();

		enums::eBTState Run() override;
	public:
		void Birthguupy();
	private:
		BlackBoard* _BlackBoard;
		int _Flag;
		float _ZPosition;
	};
}
