#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace ly
{
	HealthComponent::HealthComponent(float healt, float maxHealth)
		:m_healt{healt},
		m_maxHealth{maxHealth}
	{
	}

	void HealthComponent::ChangeHealth(float amt)
	{
		if (amt == 0) return;
		if (m_healt == 0) return;

		m_healt += amt;
		if (m_healt < 0) m_healt = 0;
		if (m_healt > m_maxHealth) m_healt = m_maxHealth;

		if (amt < 0)
		{
			TakenDamage(-amt);
			if (m_healt <= 0)
			{
				HealthEmpty();
			}
		}
		else
		{
			HealthRegen(amt);
		}

	}

	void HealthComponent::TakenDamage(float amt)
	{
		LOG("TOOK DAMAGE: %f, health is: %f/%f", amt, m_healt, m_maxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		LOG("Health Empty");
	}

	void HealthComponent::HealthRegen(float amt)
	{
		LOG("Health regen: %f, health is: %f/%f", amt, m_healt, m_maxHealth);
	}
}