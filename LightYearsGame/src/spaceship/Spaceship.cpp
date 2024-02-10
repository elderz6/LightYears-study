#include "spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{owningWorld, texturePath},
		m_velocity{}
	{

	}
	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f newVelocity)
	{
		m_velocity = newVelocity;
	}

	void Spaceship::Shoot()
	{
	}
	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}
}