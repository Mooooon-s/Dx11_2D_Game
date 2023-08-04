#pragma once
#include "MnBtNode.h"
#include "MnBlackBoard.h"

namespace Mn
{

	class DecoratorNode : public Node
	{
	public:
		DecoratorNode();
		DecoratorNode(BlackBoard* blackboard);
	public:
		Node* GetChildren() const { return _Child; }
		template<typename T>
		T* SetChild()
		{
			T* child = new T(_BlackBoard);
			_Child = child;
			return child;
		}
	private:
		Node* _Child;
		BlackBoard* _BlackBoard;
	};

}