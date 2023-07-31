#pragma once
#include "MnCompositeNode.h"

namespace Mn
{

	class RandomSelector : public CompositeNode 
	{ 
	public:
		virtual enums::eBTState Run() override {
			for (Node* child : ChildrenSuffl()) {
				if (child->Run()== enums::eBTState::SUCCESS)
					return enums::eBTState::SUCCESS;
			}
			return enums::eBTState::FAILURE;
		}
	};
}