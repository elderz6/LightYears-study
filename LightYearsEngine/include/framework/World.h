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

		template<typename ActorType, typename ... Args>
		weak<ActorType> SpawnActor(Args... args);

		sf::Vector2u GetWindowSize() const;
		void CleanCycle();
		
	private:
		void BeginPlay();
		void Tick(float deltaTime);

		Application* m_owningApp;
		bool m_beginPlay;

		List<shared<Actor>> m_actors;
		List<shared<Actor>> m_pendingActors;
	};

	template<typename ActorType, typename ... Args>
	inline weak<ActorType> World::SpawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType(this, args...)};
		m_pendingActors.push_back(newActor);
		return newActor;
	}
}