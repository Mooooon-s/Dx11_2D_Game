#include "MnCompositeNode.h"
#include <random>

namespace Mn
{
    CompositeNode::CompositeNode()
        : _Blackboard(nullptr)
        , _Child{}
    {
    }
    CompositeNode::CompositeNode(BlackBoard* blackboard)
        : _Blackboard(blackboard)
        , _Child{}
    {
    }
    std::vector<Node*> CompositeNode::ChildrenSuffl()
    {
        std::vector<Node*> temp = _Child;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(temp.begin(), temp.end(), gen);
        return temp;
    }
}