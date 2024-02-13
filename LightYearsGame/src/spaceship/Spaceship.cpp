#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{owningWorld, texturePath},
		m_velocity{},
		m_healthComp{100.f, 100.f},
		m_blinkTime{0},
		m_blinkDuration{0.2f},
		m_blinkColorOffset{255, 0, 0, 255}
	{

	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);
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

	void Spaceship::Blink()
	{
		if (m_blinkTime == 0)
		{
			m_blinkTime = m_blinkDuration;
		}
	}

	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (m_blinkTime > 0)
		{
			m_blinkTime -= deltaTime;
			m_blinkTime = m_blinkTime > 0 ? m_blinkTime : 0.f;

			GetSprite().setColor(LerpColor(sf::Color::White, m_blinkColorOffset, m_blinkTime));
		}
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{
		Blink();
	}

	void Spaceship::Blow()
	{
		Destroy();
	}
}