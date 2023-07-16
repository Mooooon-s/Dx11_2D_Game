#pragma once
#include "MoonEngine.h"

namespace Mn {
	class Entity
	{
	private:
		std::wstring _Name;
		UINT64 _ID;
		UINT64 _ColliderID;
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { _Name = name; }
		std::wstring& GetName() { return _Name; }
		void SetID(UINT64 id) { _ID = id; }
		UINT64 GetID() { return _ID; }
		void SetColliderID(UINT64 id) { _ColliderID = id; }
		UINT64 GetColliderID() { return _ColliderID; }
	};
}



