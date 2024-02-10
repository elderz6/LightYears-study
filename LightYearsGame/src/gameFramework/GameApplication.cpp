#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"
#include "spaceship/Spaceship.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"

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
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();

		testPlayer = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testPlayer.lock()->SetActorLocation(sf::Vector2f(300.f, 480.f));
		testPlayer.lock()->SetActorRotation(-90.f);
		//testPlayer.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));
		//m_counter = 0;
	}

	void GameApplication::Tick(float deltaTime)
	{
		/*m_counter += deltaTime;
		if (m_counter >= 2.f)
		{
			if (!actorToDestroy.expired())
			{
				actorToDestroy.lock()->Destroy();
			}
		}*/
	}
}