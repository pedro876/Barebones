#pragma once

#include <vector>
#include <string>
#include "File.h"

template<typename Asset>
class DB
{
public:
	DB() = delete;

	static Asset* LoadAsset(const std::string& path)
	{
		std::string text = File::Read(path);

		Asset asset = Asset();
		asset.Deserialize(text);
		instances.push_back(std::move(asset));


	}

	static void UnloadAsset(Asset& asset)
	{
		instances.erase(asset);
	}

private:
	static std::vector<Asset> instances;
};
