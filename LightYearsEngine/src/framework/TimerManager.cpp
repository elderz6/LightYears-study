#include "framework/TimerManager.h"

namespace ly
{
	Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
		:m_listener{ weakRef, callback },
		m_duration{ duration },
		m_repeat{ repeat },
		m_timeCounter{ 0 },
		m_isExpired{ false }
	{
	}

	void Timer::TickTime(float deltaTime)
	{
		if (Expired()) return;

		m_timeCounter += deltaTime;
		if (m_timeCounter >= m_duration)
		{
			m_listener.second();
			
			if (m_repeat)
			{
				m_timeCounter = 0.f;
			}
			else
			{
				SetExpired();
			}
		}
	}

	bool Timer::Expired() const
	{
		return m_isExpired || m_listener.first.expired() || m_listener.first.lock()->IsPendingDestroy();
	}

	void Timer::SetExpired()
	{
		m_isExpired = true;
	}

	unique<TimerManager> TimerManager::timerManager{ nullptr };

	TimerManager::TimerManager()
		:m_timers{}
	{
	}

	TimerManager& TimerManager::Get()
	{
		if (!timerManager)
		{
			timerManager = std::move(unique<TimerManager>(new TimerManager{}));
		}
		return *timerManager;
	}

	void TimerManager::UpdateTimer(float deltaTime)
	{
		for (Timer& timer : m_timers)
		{
			timer.TickTime(deltaTime);
		}
	}

}