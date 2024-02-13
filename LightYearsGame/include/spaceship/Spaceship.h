#pragma once
#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* owningWorld, const std::string& texturePath = "");
		virtual void Tick(float deltaTime) override;
		void SetVelocity(const sf::Vector2f newVelocity);
		sf::Vector2f GetVelocity() const { return m_velocity; };

		virtual void Shoot();
		virtual void BeginPlay() override;

	private:
		void OnHealthChanged(float amt, float health, float maxHealth);
		sf::Vector2f m_velocity;
		HealthComponent m_healthComp;
	};
}