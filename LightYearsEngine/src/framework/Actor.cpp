#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: m_owningWorld{owningWorld},
		m_hasBeganPlay{false},
		m_sprite{},
		m_texture{}
	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		LOG("Actor destroyed")
	}

	void Actor::BeginPlayInternal()
	{
		if (!m_hasBeganPlay)
		{
			m_hasBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);
		}
	}

	void Actor::BeginPlay()
	{
	}

	void Actor::Tick(float deltaTime)
	{
		//LOG("Actor Tick")
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		m_texture = AssetManager::Get().LoadTexture(texturePath);
		if (!m_texture) return;

		m_sprite.setTexture(*m_texture);

		int textureWidth = m_texture->getSize().x;
		int textureHeight = m_texture->getSize().y;
		m_sprite.setTextureRect(sf::IntRect(sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight}));
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(m_sprite);
	}

	void Actor::SetActorLocation(const sf::Vector2f& newLocation)
	{
		m_sprite.setPosition(newLocation);
	}

	void Actor::SetActorRotation(float newRot)
	{
		m_sprite.setRotation(newRot);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}

	void Actor::AddActorRotationOffset(float offsetAmt)
	{
		SetActorRotation(GetActorRotation() + offsetAmt);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return m_sprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return m_sprite.getRotation();
	}

	sf::Vector2f Actor::GetActorForwardDirection()
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection()
	{
		return RotationToVector(GetActorRotation() + 90.f);
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return m_owningWorld->GetWindowSize();
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return m_sprite.getGlobalBounds();
	}


	bool Actor::IsActorOOB() const
	{
		float windowWidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;

		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorPosition = GetActorLocation();
		
		if (actorPosition.x < -width)
		{
			return true;
		}
		if (actorPosition.x > windowWidth + width)
		{
			return true;
		}
		if (actorPosition.y < -height)
		{
			return true;
		}
		if (actorPosition.y > windowHeight + height)
		{
			return true;
		}
		return false;
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = m_sprite.getGlobalBounds();
		m_sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}
}