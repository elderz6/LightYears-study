#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"

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
		LOG("Begin play")
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
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(m_sprite);
	}
}