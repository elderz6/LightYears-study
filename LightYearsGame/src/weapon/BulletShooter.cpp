#include "weapon/BulletShooter.h"
#include "framework/Core.h"

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
		LOG("SHOOTING");
	}
}