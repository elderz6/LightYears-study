#include "weapon/Bullet.h"

namespace ly
{
	Bullet::Bullet(World* owningWorld, Actor* owner, const std::string& texturePath, float speed, float damage)
		:Actor{owningWorld, texturePath},
		m_owner{owner},
		m_speed{speed},
		m_damage{damage}
	{
	}

	void Bullet::SetSpeed(float newSpeed)
	{
		m_speed = newSpeed;
	}

	void Bullet::SetDamage(float newDamage)
	{
		m_damage = newDamage;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);
		if (IsActorOOB())
		{
			Destroy();
		}
	}

	void Bullet::Move(float deltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * m_speed * deltaTime);
	}
}