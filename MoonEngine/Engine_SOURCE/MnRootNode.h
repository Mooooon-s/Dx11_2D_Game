#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{
	class RootNode : public Node
	{
	public:
		RootNode() : _Child(nullptr), _BlackBoard(nullptr) {}
		RootNode(BlackBoard* blackboard)
			:_BlackBoard(blackboard)
			, _Child(nullptr)
		{

		}
	public:
		//void setChild(Node* newChild) { _Child = newChild; }
		template <typename T>
		T* setChild()
		{
			T* child = new T(_BlackBoard);
			_Child = child;
			return child;
		}
		virtual enums::eBTState Run() override;
		bool CheckRunning();
	private:
		Node* _Child;
		Node* _RunningNode;
		BlackBoard* _BlackBoard;
	};
}
