#pragma once
#include <iostream>
#include <map>
#include <assert.h>
#include "MnBtNode.h"

namespace Mn
{
	class BlackBoard
	{
	public:
		BlackBoard();
	public:
		template <typename T>
		T* AddData(std::wstring key, T* data)
		{
			_BlackBoard.insert(std::make_pair(key, data));
			return data;
		}
		template <typename T>
		T* MakeData(std::wstring key)
		{
			auto iter = _BlackBoard.find(key);
			if (iter != _BlackBoard.end())
				return nullptr;

			T* makeData = new T();
			_BlackBoard.insert(std::make_pair(key, makeData));
			return makeData;
		}
		template <typename T>
		T* SetData(std::wstring key, T data)
		{
			auto iter = _BlackBoard.find(key);
			if (iter == _BlackBoard.end())
				return nullptr;

			*(T*)iter->second = data;
		}
		template <typename T>
		T* GetData(std::wstring key)
		{
			auto iter = _BlackBoard.find(key);
			if (iter == _BlackBoard.end())
				return nullptr;

			return (T*)iter->second;
		}
		template <typename T>
		T GetDataValue(std::wstring key)
		{
			auto iter = _BlackBoard.find(key);
			if (iter == _BlackBoard.end())
				assert(true);
				

			return *(T*)iter->second;
		}
		template <typename T>
		void EraseData(std::wstring key)
		{
			auto iter = _BlackBoard.find(key);
			if (iter == _BlackBoard.end())
				assert(true);

			iter->second = nullptr;
			_BlackBoard.erase(iter);
		}

	template <typename T>
	void SetRunningNode(T* runningNode)
	{
		Node* node = dynamic_cast<Node*>(runningNode);
		_RunningNode = &node;
	}
	Node** GetRunningNode();

	void ResetRunningNode();

	private:
		std::map<std::wstring, void*> _BlackBoard;
		Node** _RunningNode;
	};
}