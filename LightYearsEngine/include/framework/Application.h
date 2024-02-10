#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
	class World;
	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();
		sf::Vector2u GetWindowSize() const;



	private:
		void TickInternal(float deltaTime);
		void RenderInternal();
		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow m_window;
		float m_targetFrameRate;
		sf::Clock m_tickClock;

		shared<World> currentWorld;
		sf::Clock m_cleanCycleClock;
		float m_cleanCycleInterval;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		currentWorld = newWorld;
		currentWorld->BeginPlayInternal();
		return newWorld;
	}
}