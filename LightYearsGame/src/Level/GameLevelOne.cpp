#include "level/GameLevelOne.h"
#include "spaceship/Spaceship.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"


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
		//testPlayer.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));
	}
}