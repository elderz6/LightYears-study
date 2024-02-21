#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <functional>

namespace ly
{
	struct Timer
	{
	public:
		Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat);
		void TickTime(float deltaTime);
		bool Expired() const;
		void SetExpired();
	private:
		std::pair<weak<Object>, std::function<void()>> m_listener;
		float m_duration;
		float m_timeCounter;
		bool m_repeat;
		bool m_isExpired;
	};

	class TimerManager
	{
	public:
		static TimerManager& Get();

		template<typename ClassName>
		void SetTimer(weak<Object> weakRef, void(ClassName::* callback)(), float duration, bool repeat = false)
		{
			m_timers.push_back(Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)();}, duration, repeat));
		}
		void UpdateTimer(float deltaTime);

	protected:
		TimerManager();
	private:
		static unique<TimerManager> timerManager;
		List<Timer> m_timers;

	};
}