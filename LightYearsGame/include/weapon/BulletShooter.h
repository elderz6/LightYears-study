#pragma once
#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace ly
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float cooldownTime = 0.5);

		virtual bool IsOnCooldown() const override;


	private:
		virtual void ShootImpl() override;

		sf::Clock m_cooldownClock;
		float m_CooldownTime;

	};
}