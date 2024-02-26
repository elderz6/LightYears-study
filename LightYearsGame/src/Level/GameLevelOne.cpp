#include "level/GameLevelOne.h"
#include "spaceship/Spaceship.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
#include "framework/TimerManager.h"


namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{ owningApp }
	{
		testPlayer = SpawnActor<PlayerSpaceship>();
		testPlayer.lock()->SetActorLocation(sf::Vector2f(300.f, 480.f));
		testPlayer.lock()->SetActorRotation(-90.f);

		weak<Vanguard> testSpaceship = SpawnActor<Vanguard>();
		testSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });

	}

	void GameLevelOne::BeginPlay()
	{
		timerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback_test, 1, true);
	}

	void GameLevelOne::TimerCallback_test()
	{
		LOG("callback called");
		TimerManager::Get().ClearTimer(timerHandle);
	}
}