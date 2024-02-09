#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		:Spaceship{owningWorld, path},
		m_moveInput{},
		m_speed{200}
	{

	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_moveInput.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_moveInput.y = 1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_moveInput.x = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_moveInput.x = 1.f;
		}

	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(m_moveInput * m_speed);
		m_moveInput.x = m_moveInput.y = 0.f;
	}
}