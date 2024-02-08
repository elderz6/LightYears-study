#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		:Application{600, 900, "LightYears", sf::Style::Titlebar | sf::Style::Close}
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		actorToDestroy.lock()->SetTexture("C:/Users/elder/Desktop/GameCpp/LightYears/LightYearsGame/assets/SpaceShooterRedux/PNG/playerblue.png");
		m_counter = 0;
	}

	void GameApplication::Tick(float deltaTime)
	{
		m_counter += deltaTime;
		if (m_counter >= 2.f)
		{
			if (!actorToDestroy.expired())
			{
				actorToDestroy.lock()->Destroy();
			}
		}
	}
}