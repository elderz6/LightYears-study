#pragma once
#include "framework/Delegate.h"

namespace ly
{
	class HealthComponent
	{
	public:
		HealthComponent(float healt, float maxHealth);

		void ChangeHealth(float amt);
		float GetHealth() { return m_health; };
		float GetMaxHealth() { return m_maxHealth; };

		Delegate<float, float, float> onHealthChanged;
		Delegate<float, float, float> onTakenDamage;
		Delegate<> onHealthEmpty;

	private:
		void TakenDamage(float amt);
		void HealthEmpty();

		float m_health;
		float m_maxHealth;
	};
}