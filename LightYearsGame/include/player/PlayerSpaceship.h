#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
	class BulletShooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerblue.png");

		virtual void Tick(float deltaTime) override;
		void SetSpeed(float newSpeed) { m_speed = newSpeed; };
		float GetSpeed() { return m_speed; };

		virtual void Shoot() override;

	private:
		void HandleInput();
		void NormalizeInput();
		void ClampInputOnEdge();
		void ConsumeInput(float deltaTime);
		sf::Vector2f m_moveInput;
		float m_speed;

		unique<BulletShooter> m_shooter;
	};
}