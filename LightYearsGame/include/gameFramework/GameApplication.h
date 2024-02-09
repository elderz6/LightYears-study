#pragma once
#include <framework/Application.h>
#include "framework/Core.h"

namespace ly
{
	class Actor;
	class SpaceShip;
	class GameApplication : public Application
	{
	public:
		GameApplication();
		virtual void Tick(float deltaTime) override;

	private:
		float m_counter;
		weak<Actor> testPlayer;

	};
}