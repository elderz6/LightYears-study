#pragma once
#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace ly
{
	class Actor;

	class PhysicsContactListener : public b2ContactListener
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();
		void Step(float deltaTime);
		b2Body* AddListener(Actor* listener);
		float GetPhysicsScale() const { return m_physicsScale; };
		void RemoveListener(b2Body* body);

	protected:
		PhysicsSystem();

	private:
		static unique<PhysicsSystem> physicsSystem;
		b2World m_physicsWorld;
		float m_physicsScale;

		int m_velocityIterations;
		int m_positionIterations;
		PhysicsContactListener m_contactListener;
	};
}