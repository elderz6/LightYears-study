#pragma once
#include "framework/Delegate.h"

namespace ly
{
	class HealthComponent
	{
	public:
		HealthComponent(float healt, float maxHealth);

		void ChangeHealth(float amt);
		float GetHealth() { return m_healt; };
		float GetMaxHealth() { return m_maxHealth; };

		Delegate<float, float, float> onHealthChanged;

	private:
		void TakenDamage(float amt);
		void HealthEmpty();
		void HealthRegen(float amt);

		float m_healt;
		float m_maxHealth;
	};
}