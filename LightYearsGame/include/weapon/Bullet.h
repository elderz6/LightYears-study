#pragma once
#include "framework/Actor.h"

namespace ly
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* owningWorld, Actor* owner,
			const std::string& texturePath,
			float speed = 600.f, float damage = 10.f);

		void SetSpeed(float newSpeed);
		void SetDamage(float newDamage);
		float GetDamage() const { return m_damage; };
		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;

		void Move(float deltaTime);
		Actor* m_owner;
		float m_speed;
		float m_damage;
	};

}