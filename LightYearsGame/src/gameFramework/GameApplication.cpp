#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "config.h"
#include "framework/AssetManager.h"
#include "Level/GameLevelOne.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		:Application{600, 900, "LightYears", sf::Style::Titlebar | sf::Style::Close}
	{

		AssetManager::Get().SetAssetRootDir(GetResourceDir());
		weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();
	}
}