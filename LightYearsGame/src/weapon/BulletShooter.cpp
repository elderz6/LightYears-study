#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime)
		:Shooter{owner},
		m_cooldownClock{},
		m_CooldownTime{ cooldownTime }
	{

	}
	bool BulletShooter::IsOnCooldown() const
	{
		if (m_cooldownClock.getElapsedTime().asSeconds() > m_CooldownTime)
		{
			return false;
		}

		return true;
	}

	void BulletShooter::ShootImpl()
	{
		m_cooldownClock.restart();
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation());
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation());
	}
}