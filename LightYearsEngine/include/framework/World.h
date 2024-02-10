#pragma once
#include "framework/Core.h"
#include "SFML/Graphics.hpp"

namespace ly
{
	class Actor;
	class Application;
	class World
	{
	public:
		World(Application* owningApp);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		virtual ~World();

		template<typename ActorType>
		weak<ActorType> SpawnActor();

		sf::Vector2u GetWindowSize() const;
		
	private:
		void BeginPlay();
		void Tick(float deltaTime);

		Application* m_owningApp;
		bool m_beginPlay;

		List<shared<Actor>> m_actors;
		List<shared<Actor>> m_pendingActors;
	};

	template<typename ActorType>
	inline weak<ActorType> World::SpawnActor()
	{
		shared<ActorType> newActor{ new ActorType{this} };
		m_pendingActors.push_back(newActor);
		return newActor;
	}
}