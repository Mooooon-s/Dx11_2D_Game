#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class FindCoin : public Node
	{
	public:
		FindCoin();
		FindCoin(BlackBoard* board);
		~FindCoin();

		virtual enums::eBTState Run() override;
	public:
		void NearestCoin(std::vector<GameObject*> coin);

		void ResetDistance() { _NearestDistance = Vector3(999.0f, 999.0f, 999.0f); }
	private:
		BlackBoard* _BlackBoard;
		Vector3 _NearestDistance;
	};
}
