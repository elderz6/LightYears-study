#pragma once
#include "framework/Object.h"
#include "SFML/Graphics.hpp"
#include "framework/Core.h"

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

		void SetActorLocation(const sf::Vector2f& newLocation);
		void SetActorRotation(float newRot);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt);

		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;

		sf::Vector2f GetActorForwardDirection();
		sf::Vector2f GetActorRightDirection();

	private:
		void CenterPivot();
		World* m_owningWorld;
		bool m_hasBeganPlay;

		sf::Sprite m_sprite;
		shared<sf::Texture> m_texture;
	};
}