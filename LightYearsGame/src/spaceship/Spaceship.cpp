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
		m_healthComp.onTakenDamage.BindAction(selfRef, &Spaceship::OnTakenDamage);
		m_healthComp.onHealthEmpty.BindAction(selfRef, &Spaceship::Blow);
	}

	void Spaceship::ApplyDamage(float amt)
	{
		m_healthComp.ChangeHealth(-amt);
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{
	}

	void Spaceship::Blow()
	{
		Destroy();
	}
}