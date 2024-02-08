#pragma once
#include "framework/Object.h"
#include "SFML/Graphics.hpp"

namespace ly
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void SetTexture(const std::string& texturePath);

		void Render(sf::RenderWindow& window);

	private:
		World* m_owningWorld;
		bool m_hasBeganPlay;

		sf::Sprite m_sprite;
		sf::Texture m_texture;
	};
}