#pragma once
#include "framework/Object.h"
#include "SFML/Graphics.hpp"
#include "framework/Core.h"

class b2Body;
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
		sf::Vector2u GetWindowSize() const;
		sf::FloatRect GetActorGlobalBounds() const;

		const World* GetWorld() const { return m_owningWorld; };
		World* GetWorld() { return m_owningWorld; };

		bool IsActorOOB(float allowance = 10.f) const;
		bool SetEnablePhysics(bool enable);
		virtual void OnActorBeginOverlap(Actor* actor);
		virtual void OnActorEndOverlap(Actor* actor);
		virtual void Destroy() override;

		static uint8 GetNeutralTeamID() { return neutralTeamID; };
		void SetTeamID(uint8 teamID) { m_teamID = teamID; };
		uint8 GetTeamId() const { return m_teamID; };
		bool IsOtherHostile(Actor* other) const;

		virtual void ApplyDamage(float amt);

		sf::Sprite& GetSprite() { return m_sprite; };
		const sf::Sprite& GetSprite() const { return m_sprite; };

	private:
		void InitializePhysics();
		void UnInitializePhysics();
		void UpdatePhysicsBodyTransform();
		void CenterPivot();
		World* m_owningWorld;
		bool m_hasBeganPlay;

		sf::Sprite m_sprite;
		shared<sf::Texture> m_texture;

		bool m_physicsEnabled;
		b2Body* m_physicsBody;

		uint8 m_teamID;

		const static uint8 neutralTeamID = 255;
	};
}