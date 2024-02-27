#include "gameplay/GameStage.h"
#include "framework/World.h"
#include "framework/Core.h"

namespace ly
{
	GameStage::GameStage(World* world)
		: m_world{ world },
		m_stageFinished{ false }
	{
	}

	void GameStage::StartStage()
	{
		LOG("Stage Started");
	}

	void GameStage::TickStage(float deltaTime)
	{
	}

	void GameStage::FinishStage()
	{
		onStageFinished.Broadcast();
		m_stageFinished = true;
		StageFinished();
	}

	void GameStage::StageFinished()
	{
		LOG("Stage Finished");
	}
}