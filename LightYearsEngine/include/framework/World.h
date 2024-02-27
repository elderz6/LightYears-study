#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include "SFML/Graphics.hpp"

namespace ly
{
	class Actor;
	class Application;
	class GameStage;
	class World : public Object
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
		void AddStage(const shared<GameStage> newStage);
		
	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		Application* m_owningApp;
		bool m_beginPlay;

		List<shared<Actor>> m_actors;
		List<shared<Actor>> m_pendingActors;

		List<shared<GameStage>> m_gameStages;
		int m_currentStageIndex;

		virtual void InitGameStages();
		virtual void AllGameStagesFinished();
		void NextGameStage();
	};

	template<typename ActorType, typename ... Args>
	inline weak<ActorType> World::SpawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType(this, args...)};
		m_pendingActors.push_back(newActor);
		return newActor;
	}
}