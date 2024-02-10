#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"

namespace ly
{

	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: m_window{ sf::VideoMode(windowWidth, windowHeight), title, style },
		m_targetFrameRate{ 60 },
		m_tickClock{},
		currentWorld{ nullptr },
		m_cleanCycleClock{},
		m_cleanCycleInterval{2.f}
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

	sf::Vector2u Application::GetWindowSize() const
	{
		return m_window.getSize();
	}


	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (currentWorld)
		{
			currentWorld->TickInternal(deltaTime);
		}

		if (m_cleanCycleClock.getElapsedTime().asSeconds() >= m_cleanCycleInterval)
		{
			m_cleanCycleClock.restart();
			AssetManager::Get().CleanCycle();
			if (currentWorld)
			{
				currentWorld->CleanCycle();
			}
		}
	}

	void Application::RenderInternal()
	{
		m_window.clear();

		Render();

		m_window.display();
	}

	void Application::Render()
	{
		if (currentWorld)
		{
			currentWorld->Render(m_window);
		}
	}

	void Application::Tick(float deltaTime)
	{
	}
}