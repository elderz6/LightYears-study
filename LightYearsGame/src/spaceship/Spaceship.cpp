#include "spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{owningWorld, texturePath},
		m_velocity{},
		m_healthComp{100.f, 100.f}
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

		weak<Object> selfRef = GetWeakRef();
		m_healthComp.onHealthChanged.BindAction(selfRef, &Spaceship::OnHealthChanged);
		m_healthComp.onHealthChanged.Broadcast(10, 80, 100);
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{
		LOG("amt %f health %f maxHealth %f", amt, health, maxHealth);
	}
}