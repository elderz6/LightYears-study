#include "framework/Application.h"
#include <iostream>

namespace ly
{

	Application::Application()
		: m_window{ sf::VideoMode(800, 600), "LightYears" },
		m_targetFrameRate{60},
		m_tickClock{}
	{
	}

	void Application::Run()
	{
		m_tickClock.restart();

		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / m_targetFrameRate;


		while (m_window.isOpen())
		{
			sf::Event windowEvent;
			while (m_window.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					m_window.close();
				}
			}

			accumulatedTime += m_tickClock.restart().asSeconds();
			while (accumulatedTime > targetDeltaTime) 
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	void Application::RenderInternal()
	{
		m_window.clear();

		Render();

		m_window.display();
	}

	void Application::Render()
	{
		sf::RectangleShape rect{ sf::Vector2f{100, 100} };
		rect.setFillColor(sf::Color::Green);
		rect.setOrigin(50, 50);
		rect.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
		m_window.draw(rect);
	}

	void Application::Tick(float deltaTime)
	{
		std::cout << "Tick at framerate " << 1.f / deltaTime << std::endl;
	}
}