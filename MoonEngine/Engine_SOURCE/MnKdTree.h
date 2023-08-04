#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class KdNode
	{
	public:
		Vector3 _Min;
		Vector3 _Max;
		std::vector<GameObject*> _GameObj;
		KdNode* _ChildNode[2];
	public:
		KdNode();
		KdNode(Vector3 min, Vector3 max);
		KdNode(int depth, Vector3 min, Vector3 max);
		~KdNode();
	public:
		inline Vector3 GetCenter() { return (_Max + _Min) / 2.0f; }
	public:
		bool IsEmpty();
		bool IsContain(Vector3 p);
		bool IsContain(Vector3 p, double r);
		bool IsIntersect(Vector3 p, double r);
		void SubDivide();
	};
	class KdTree
	{
	public:
		int						_Bucket;
		KdNode					*_Root;
		std::vector<KdNode*>	_DrawNodes;
	public:
		KdTree();
		KdTree(int bucket) { _Bucket = bucket; }
		~KdTree();
	public:
		void BuildTree(std::vector<GameObject*>& gameObj);
		void Query(std::vector<GameObject*>& gameObj, double r, int index);
		void Query(GameObject* gameObj, double r);
	public:
		void Draw();
	};

}