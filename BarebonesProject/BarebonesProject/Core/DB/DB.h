#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

namespace Barebones
{
	template<typename T>
	class DB
	{
	public:
		DB() = delete;

		static std::weak_ptr<T> Get(const std::string& path)
		{
			return pathToAsset[path];
		}

		static std::weak_ptr<T> Register(std::shared_ptr<T> asset)
		{
			auto [it, inserted] = pathToAsset.emplace(asset->GetPath(), std::move(asset));

			if (!inserted)
			{
				throw std::runtime_error("Asset with path '" + asset->GetPath() + "' already registered.");
			}

			return it->second;
		}

		static bool Release(std::weak_ptr<T> asset)
		{
			if (auto sharedPtr = asset.lock())
			{
				return pathToAsset.erase(sharedPtr->GetPath());
			}
			else
			{
				return false;
			}
		}

	private:
		static inline std::unordered_map<std::string, std::shared_ptr<T>> pathToAsset;
	};
}

