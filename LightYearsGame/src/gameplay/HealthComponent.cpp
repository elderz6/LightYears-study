#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace ly
{
	HealthComponent::HealthComponent(float healt, float maxHealth)
		:m_health{healt},
		m_maxHealth{maxHealth}
	{
	}

	void HealthComponent::ChangeHealth(float amt)
	{
		if (amt == 0) return;
		if (m_health == 0) return;

		m_health += amt;
		if (m_health < 0) m_health = 0;
		if (m_health > m_maxHealth) m_health = m_maxHealth;

		if (amt < 0)
		{
			TakenDamage(-amt);
			if (m_health <= 0)
			{
				HealthEmpty();
			}
		}

		onHealthChanged.Broadcast(amt, m_health, m_maxHealth);

	}

	void HealthComponent::TakenDamage(float amt)
	{
		onTakenDamage.Broadcast(amt, m_health, m_maxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		onHealthEmpty.Broadcast();
	}

}