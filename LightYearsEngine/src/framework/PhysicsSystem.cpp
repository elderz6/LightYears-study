#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>
#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

namespace ly
{
	unique<PhysicsSystem> PhysicsSystem::physicsSystem{ nullptr };

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!physicsSystem)
		{
			physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
		}
		return *physicsSystem;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
		ProcessPendingRemoveListeners();
		m_physicsWorld.Step(deltaTime, m_velocityIterations, m_positionIterations);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->IsPendingDestroy())
		{
			return nullptr;
		}

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);

		bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(),
			listener->GetActorLocation().y * GetPhysicsScale());

		bodyDef.angle = DegreesToRadians(listener->GetActorRotation());
		b2Body* body = m_physicsWorld.CreateBody(&bodyDef);

		b2PolygonShape shape;
		auto bound = listener->GetActorGlobalBounds();
		shape.SetAsBox(bound.width/2 * GetPhysicsScale(), bound.height / 2 * GetPhysicsScale());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* body)
	{
		m_pendingRemoveListeners.insert(body);
	}

	void PhysicsSystem::Cleanup()
	{
		physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
	}

	PhysicsSystem::PhysicsSystem()
		:m_physicsWorld{b2Vec2{0.f,0.f}},
		m_physicsScale{0.01f},
		m_velocityIterations{8},
		m_positionIterations{3},
		m_contactListener{},
		m_pendingRemoveListeners{}
	{
		m_physicsWorld.SetContactListener(&m_contactListener);
		m_physicsWorld.SetAllowSleeping(false);
	}

	void PhysicsSystem::ProcessPendingRemoveListeners()
	{
		for (auto listener : m_pendingRemoveListeners)
		{
			m_physicsWorld.DestroyBody(listener);
		}
		m_pendingRemoveListeners.clear();
	}

	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (ActorA && !ActorA->IsPendingDestroy())
		{
			ActorA->OnActorBeginOverlap(ActorB);
		}
		if (ActorB && !ActorB->IsPendingDestroy())
		{
			ActorB->OnActorBeginOverlap(ActorA);
		}
	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* ActorA = nullptr;
		Actor* ActorB = nullptr;

		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
		{
			ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}
		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
		{
			ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		}
		if (ActorA && !ActorA->IsPendingDestroy())
		{
			ActorA->OnActorEndOverlap(ActorB);
		}
		if (ActorB && !ActorB->IsPendingDestroy())
		{
			ActorB->OnActorEndOverlap(ActorA);
		}
	}
}