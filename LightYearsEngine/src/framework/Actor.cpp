#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
	Actor::Actor(World* owningWorld)
		: m_owningWorld{owningWorld},
		m_hasBeganPlay{false}
	{
	}

	Actor::~Actor()
	{
	}

	void Actor::BeginPlayInternal()
	{
		if (!m_hasBeganPlay)
		{
			m_hasBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::BeginPlay()
	{
		LOG("Begin play")
	}

	void Actor::Tick(float deltaTime)
	{
		LOG("Actor Tick")
	}
}