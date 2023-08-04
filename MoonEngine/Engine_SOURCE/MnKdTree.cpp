#include "MnKdTree.h"
#include "MnTransform.h"
namespace Mn
{
	KdNode::KdNode()
	{
		for (int i = 0; i < 2; i++)
		{
			_ChildNode[i] = nullptr;
		}
	}
	KdNode::KdNode(Vector3 min, Vector3 max)
	{
		_Min = min;
		_Max = max;
		for (int i = 0; i < 2; i++)
		{
			_ChildNode[i] = nullptr;
		}
	}
	KdNode::KdNode(int depth, Vector3 min, Vector3 max)
	{
		_Min = min;
		_Max = max;
		for (int i = 0; i < 2; i++)
		{
			_ChildNode[i] = nullptr;
		}
	}
	KdNode::~KdNode()
	{
	}
	bool KdNode::IsEmpty()
	{
		return _ChildNode[0]==nullptr;
	}
	bool KdNode::IsContain(Vector3 p)
	{
		if(p.x >= _Min.x && p.x<= _Max.x && p.y >= _Min.y && _Max.y<=p.y)
			return true;
		return false;
	}
	bool KdNode::IsContain(Vector3 p, double r)
	{
		double minx = p.x - r;
		double maxx = p.x + r;
		double miny = p.y - r;
		double maxy = p.y + r;
		return (minx >= _Min.x && maxx <= _Max.x && miny >= _Min.y && maxy <= _Max.y);
	}
	bool KdNode::IsIntersect(Vector3 p, double r)
	{
		double dist = 0.0f;
		for (int i = 0; i < 2; i++)
		{
			if ((p.x + i) < _Min.x + i)
			{
				double d = (_Min.x + i) - (p.x + i);
				dist += d * d;
			}
			else if ((p.x + i) > (_Min.x + i))
			{
				double d = (p.x + i) - (_Min.x + i);
				dist += d * d;
			}
		}
		return dist <= r * r;
	}
	void KdNode::SubDivide()
	{
		for (int i = 0; i < 2; i++)
		{
			_ChildNode[i] = new KdNode();
		}

		auto crossVect = _Max - _Min;
		int mid = _GameObj.size() / 2;
		int splitAxis = crossVect.x > crossVect.y ? 0 : 1 ;
		std::nth_element(_GameObj.begin(), _GameObj.begin() + mid, _GameObj.end(), 
			[splitAxis](GameObject* a, GameObject* b)
			{ 
				if (splitAxis == 0)
				{
					if ((a->GetComponent<Transform>()->Position().x) < (b->GetComponent<Transform>()->Position().x))
						return true;
					return false;
				}
				else
				{
					if ((a->GetComponent<Transform>()->Position().y) < (b->GetComponent<Transform>()->Position().y))
						return true;
					return false;
				}
			});

		auto separation = *((&_GameObj[mid]));
		auto localMin = _Min;
		auto localMax = _Max;
		localMin = separation->GetComponent<Transform>()->Position();
		localMax = separation->GetComponent<Transform>()->Position();

		_ChildNode[0]->_Min = _Min;
		_ChildNode[0]->_Max = localMax;
		_ChildNode[1]->_Min = localMin;
		_ChildNode[1]->_Max = _Max;

		// Transfer GameObject
		_ChildNode[0]->_GameObj.clear();
		_ChildNode[0]->_GameObj.assign(_GameObj.begin(), _GameObj.begin() + mid);
		_ChildNode[1]->_GameObj.clear();
		_ChildNode[1]->_GameObj.assign(_GameObj.begin() + mid, _GameObj.end());
		_GameObj.clear();
	}
	KdTree::KdTree()
		: _Bucket(1)
		, _Root(nullptr)
	{
	}
	KdTree::~KdTree()
	{
	}
	void KdTree::BuildTree(std::vector<GameObject*>& gameObj)
	{
		_Root = new KdNode(1,Vector3(-10.0f,-10.0f,0.0f),Vector3(10.0f,10.0f,0.0f));
		
		for (auto g : gameObj)
		{
			_Root->_GameObj.push_back(g);
		}

		std::vector<KdNode*> queue;
		queue.push_back(_Root);

		while (queue.size()!=0)
		{
			auto node = queue[0];
			queue.erase(queue.begin());
			if (node->_GameObj.size() > _Bucket)
			{
				node->SubDivide();
				for (int i = 0; i < 2; i++)
				{
					queue.push_back(node->_ChildNode[i]);
				}
			}
		}
		int a = 0;
	}
	void KdTree::Query(std::vector<GameObject*>& gameObj, double r, int index)
	{
		Vector3 pos = gameObj[index]->GetComponent<Transform>()->Position();

		std::vector<KdNode*> queue;
		queue.push_back(_Root);

		while (queue.size() != 0)
		{
			auto node = queue[0];
			queue.erase(queue.begin());
			bool contain = node->IsContain(pos, r);
			bool intersect = node->IsIntersect(pos, r);
			if (contain == true || intersect == true)
			{
				for (auto g : node->_GameObj)
				{
					g->State(GameObject::eState::Active);
				}
				if (node->IsEmpty() == false) {
					for (int i = 0; i < 2; i++) {
						queue.push_back(node->_ChildNode[i]);
					}
				}
			}
		}
	}
	void KdTree::Query(GameObject* gameObj, double r)
	{
		Vector3 pos = gameObj->GetComponent<Transform>()->Position();

		std::vector<KdNode*> queue;
		queue.push_back(_Root);

		while (queue.size() != 0)
		{
			auto node = queue[0];
			queue.erase(queue.begin());
			bool contain = node->IsContain(pos, r);
			bool intersect = node->IsIntersect(pos, r);
			if (contain == true || intersect == true)
			{
				for (auto g : node->_GameObj)
				{
					g->State(GameObject::eState::Active);
				}
				if (node->IsEmpty() == false) {
					for (int i = 0; i < 2; i++) {
						queue.push_back(node->_ChildNode[i]);
					}
				}
			}
		}
	}
	void KdTree::Draw()
	{
	}
}