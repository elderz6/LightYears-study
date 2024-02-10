#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		:Spaceship{owningWorld, path},
		m_moveInput{},
		m_speed{200},
		m_shooter{ new BulletShooter{this} }
	{

	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (m_shooter)
		{
			m_shooter->Shoot();
		}
	}

	void PlayerSpaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
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