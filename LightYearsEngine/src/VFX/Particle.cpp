#include "VFX/Particle.h"
#include "framework/MathUtility.h"

namespace ly
{
	Particle::Particle(World* owningWorld, const std::string& texturePath)
		:Actor{owningWorld, texturePath},
		m_velocity{},
		m_lifeTime{1.f},
		m_timer{}
	{
	}

	void Particle::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		Move(deltaTime);
		Fade(deltaTime);

		if (m_timer.getElapsedTime().asSeconds() >= m_lifeTime)
		{
			Destroy();
		}
	}

	void Particle::RandomVelocity(float minSpeed, float maxSpeed)
	{
		m_velocity = RandomUnitVector() * RandomRange(minSpeed, maxSpeed);
	}

	void Particle::RandomSize(float min, float max)
	{
		float randScale = RandomRange(min, max);
		GetSprite().setScale(randScale, randScale);
	}

	void Particle::RandomLifetime(float min, float max)
	{
		m_lifeTime = RandomRange(min, max);
	}

	void Particle::Move(float deltaTime)
	{
		AddActorLocationOffset(m_velocity * deltaTime);
	}

	void Particle::Fade(float deltaTime)
	{
		float elapsedTime = m_timer.getElapsedTime().asSeconds();
		GetSprite().setColor(
			LerpColor(GetSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime / m_lifeTime)
		);
		GetSprite().setScale(
			LerpVector(GetSprite().getScale(), sf::Vector2f{ 0,0 }, elapsedTime/ m_lifeTime)
		);
	}

}