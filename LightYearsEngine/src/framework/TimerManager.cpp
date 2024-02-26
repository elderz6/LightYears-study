#include "framework/TimerManager.h"

namespace ly
{
	unsigned int TimerHandle::timerKeyCounter = 0;

	TimerHandle::TimerHandle()
		:m_timerKey{GetNextTimerKey()}
	{
	}

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
		for (auto iter = m_timers.begin(); iter != m_timers.end();)
		{
			if (iter->second.Expired())
			{
				iter = m_timers.erase(iter);
			}
			else
			{
				iter->second.TickTime(deltaTime);
				++iter;
			}
		}
	}

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
	{
		return lhs.GetTimerKey() == rhs.GetTimerKey();
	}

	void TimerManager::ClearTimer(TimerHandle timerIndex)
	{
		auto iter = m_timers.find(timerIndex);
		if (iter != m_timers.end())
		{
			iter->second.SetExpired();
		}
	}

}