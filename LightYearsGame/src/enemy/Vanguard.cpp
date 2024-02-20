#include "enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, sf::Vector2f velocity)
		:EnemySpaceship{ owningWorld, texturePath },
		m_shooter{ new BulletShooter{this} }
	{
		SetVelocity(velocity);
		SetActorRotation(90.f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void Vanguard::Shoot()
	{
		m_shooter->Shoot();
	}
}