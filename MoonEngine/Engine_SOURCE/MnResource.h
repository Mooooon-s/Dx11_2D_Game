#pragma once
#include "MnEntity.h"

//추상 클래스
namespace Mn {
	class Resource
	{
	private:
		std::wstring _Key;
		std::wstring _path;
		const enums::eResourceType _Type;
	public:
		Resource(Mn::enums::eResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

	public:
		std::wstring Key(void) { return _Key; }
		std::wstring Path(void) { return _path; }
		void Key(const std::wstring& Key) { _Key = Key; }
		void Path(const std::wstring& path) { _path = path; }

		enums::eResourceType Type() { return _Type; }
	};
}

