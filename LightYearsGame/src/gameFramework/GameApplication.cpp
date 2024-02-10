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
		m_counter = 0;

		AssetManager::Get().SetAssetRootDir(GetResourceDir());
		weak<World> newWorld = LoadWorld<World>();

		testPlayer = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testPlayer.lock()->SetActorLocation(sf::Vector2f(300.f, 480.f));
		testPlayer.lock()->SetActorRotation(-90.f);

		weak<Spaceship> testSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
		testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_red.png");
		testSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });
		//testPlayer.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));
	}

	void GameApplication::Tick(float deltaTime)
	{
		/*m_counter += deltaTime;
		if (m_counter >= 10.f)
		{
			if (!testPlayer.expired())
			{
				testPlayer.lock()->Destroy();
			}
		}*/
	}
}