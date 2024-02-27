#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"

namespace ly
{
	World::World(Application* owningApp)
		: m_owningApp{ owningApp },
		m_beginPlay{ false },
		m_actors{},
		m_pendingActors{},
		m_currentStageIndex{-1},
		m_gameStages{}
	{

	}

	void World::BeginPlayInternal()
	{
		if (!m_beginPlay)
		{
			m_beginPlay = true;
			BeginPlay();
			InitGameStages();
			NextGameStage();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : m_pendingActors)
		{
			m_actors.push_back(actor);
			actor->BeginPlayInternal();
		}

		m_pendingActors.clear();

		for (auto iter = m_actors.begin(); iter != m_actors.end();)
		{
			iter->get()->TickInternal(deltaTime);
			++iter;
		}

		if (m_currentStageIndex >= 0 && m_currentStageIndex < m_gameStages.size())
		{
			m_gameStages[m_currentStageIndex]->TickStage(deltaTime);
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : m_actors)
		{
			actor->Render(window);
		}
	}

	World::~World()
	{
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return m_owningApp->GetWindowSize();
	}

	void World::CleanCycle()
	{
		for (auto iter = m_actors.begin(); iter != m_actors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = m_actors.erase(iter);
			}
			else ++iter;
		}

		for (auto iter = m_gameStages.begin(); iter != m_gameStages.end();)
		{
			if (iter->get()->IsStageFinished())
			{
				iter = m_gameStages.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	void World::AddStage(const shared<GameStage> newStage)
	{
		m_gameStages.push_back(newStage);
	}

	void World::BeginPlay()
	{
	}

	void World::Tick(float deltaTime)
	{
		//LOG("Ticking at framerate %f", 1.f / deltaTime);
	}

	void World::InitGameStages()
	{
	}

	void World::AllGameStagesFinished()
	{
	}

	void World::NextGameStage()
	{
		++m_currentStageIndex;
		if (m_currentStageIndex >= 0 && m_currentStageIndex < m_gameStages.size())
		{
			m_gameStages[m_currentStageIndex]->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
			m_gameStages[m_currentStageIndex]->StartStage();
		}
		else
		{
			AllGameStagesFinished();
		}
	}
}