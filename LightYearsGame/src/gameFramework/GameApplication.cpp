#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"

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

		actorToDestroy.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerblue.png");
		actorToDestroy.lock()->SetActorLocation(sf::Vector2f(300.f, 480.f));
		actorToDestroy.lock()->SetActorRotation(180.f);

		m_counter = 0;
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