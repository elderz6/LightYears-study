#pragma once
#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World* world);
		const World* GetWorld() const { return m_world; }
		World* GetWorld() { return m_world; }

		Delegate<> onStageFinished;

		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		void FinishStage();
		bool IsStageFinished() const { return m_stageFinished; }

	private:
		World* m_world;
		bool m_stageFinished;
		void StageFinished();
	};
}
