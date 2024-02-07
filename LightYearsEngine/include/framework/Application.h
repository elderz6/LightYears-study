#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
	class Application
	{
	public:
		Application();
		void Run();
	private:
		void TickInternal(float deltaTime);
		void RenderInternal();
		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow m_window;
		float m_targetFrameRate;
		sf::Clock m_tickClock;

	};
}