#pragma once
#include <vector> 
#include "MnBtNode.h"
#include "MnBlackBoard.h"
namespace Mn
{
	class CompositeNode : public Node
	{
	public:
		CompositeNode();
		CompositeNode(BlackBoard* blackboard);
	public:
		const std::vector<Node*>& GetChildren() const { return _Child; }
		template<typename T>
		T* AddChild()
		{
			T* child = new T(_Blackboard);
			_Child.push_back(child);
			return child;
		}
	private:
		std::vector<Node*> _Child;
		BlackBoard* _Blackboard;
	protected:
		std::vector<Node*> ChildrenSuffl();
	};
}

