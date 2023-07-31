#include "MnDecoratorNode.h"
namespace Mn
{
    DecoratorNode::DecoratorNode()
        : _BlackBoard(nullptr)
        , _Child(nullptr)
    {
    }
    DecoratorNode::DecoratorNode(BlackBoard* blackboard)
        : _BlackBoard(blackboard)
        , _Child(nullptr)
    {
    }
}