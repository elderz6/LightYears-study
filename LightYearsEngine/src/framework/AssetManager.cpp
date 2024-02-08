#include "framework/AssetManager.h"

namespace ly
{
	unique<AssetManager> AssetManager::assetManager{ nullptr };

	AssetManager& AssetManager::Get()
	{
		if (!assetManager)
		{
			assetManager = std::move(unique<AssetManager>{new AssetManager});
		}
		return *assetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		auto found = m_loadedTextureMap.find(path);
		if (found != m_loadedTextureMap.end())
		{
			return found->second;
		}

		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(path))
		{
			m_loadedTextureMap.insert({ path, newTexture });
			return newTexture;
		}

		return shared<sf::Texture> {nullptr};
	}

	void AssetManager::CleanCycle()
	{
		for (auto iter = m_loadedTextureMap.begin(); iter!= m_loadedTextureMap.end();)
		{
			if (iter->second.unique())
			{
				iter = m_loadedTextureMap.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	AssetManager::AssetManager()
	{
	}
}