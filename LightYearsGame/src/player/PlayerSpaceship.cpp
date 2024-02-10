#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"

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

		ClampInputOnEdge();
		NormalizeInput();
	}

	void PlayerSpaceship::NormalizeInput()
	{
		Normalize(m_moveInput);
	}

	void PlayerSpaceship::ClampInputOnEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();
		if (actorLocation.x < 0 && m_moveInput.x == -1.f)
		{
			m_moveInput.x = 0;
		}
		if (actorLocation.x > GetWindowSize().x && m_moveInput.x == 1.f)
		{
			m_moveInput.x = 0;
		}
		if (actorLocation.y < 0 && m_moveInput.y == -1.f)
		{
			m_moveInput.y = 0;
		}
		if (actorLocation.y > GetWindowSize().y && m_moveInput.y == 1.f)
		{
			m_moveInput.y = 0;
		}
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(m_moveInput * m_speed);
		m_moveInput.x = m_moveInput.y = 0.f;
	}
}