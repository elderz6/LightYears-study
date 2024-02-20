#pragma once
#include "EnemySpaceship.h"
#include "framework/Core.h"

namespace ly
{
	class BulletShooter;
	class Vanguard : public EnemySpaceship
	{
	public:
		Vanguard(World* owningWorld, 
			const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue1.png",
			const sf::Vector2f velocity = {0.f, 100.f}
		);

		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;
		unique<BulletShooter> m_shooter;

	};
}