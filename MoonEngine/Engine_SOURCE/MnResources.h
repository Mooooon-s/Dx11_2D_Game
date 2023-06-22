#pragma once
#include "MnResource.h"

namespace Mn {
	class Resources
	{
	private:
		static std::map<std::wstring, std::shared_ptr<Resource>> _Resources;
	public:
		template<typename T>
		static std::shared_ptr <T> Find(const std::wstring& key) {
			std::map<std::wstring, std::shared_ptr<Resource>>::iterator iter = _Resources.find(key);
			if (iter != _Resources.end()) 
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			return nullptr;
		}

		template<typename T>
		static std::shared_ptr <T> Load(const std::wstring& key, const std::wstring& path)
		{
			std::shared_ptr <T> resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			resource = std::make_shared<T>();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->Key(key);
			resource->Path(path);
			_Resources.insert(std::make_pair(key, resource));

			return std::dynamic_pointer_cast<T>(resource);

		}

		template <typename T>
		static void Insert(const std::wstring& key, std::shared_ptr <T>resource)
		{
			_Resources.insert(std::make_pair(key, resource));
		}

	};
}

