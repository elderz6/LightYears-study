#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <functional>

namespace ly
{
	struct TimerHandle
	{
	public:
		TimerHandle();
		unsigned int GetTimerKey() const { return m_timerKey; }
	private:
		unsigned int m_timerKey;
		static unsigned int timerKeyCounter;
		static unsigned int GetNextTimerKey() { return ++timerKeyCounter; }
	};

	struct TimerHandleHashFunction
	{
	public:
		std::size_t operator()(const TimerHandle& timerHandle) const
		{
			return timerHandle.GetTimerKey();
		}
	};

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs);

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
		TimerHandle SetTimer(weak<Object> weakRef, void(ClassName::* callback)(), float duration, bool repeat = false)
		{
			TimerHandle newHandle{};
			m_timers.insert({ newHandle, Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)();}, duration, repeat) });
			return newHandle;
		}

		void UpdateTimer(float deltaTime);
		void ClearTimer(TimerHandle timerIndex);

	protected:
		TimerManager();
	private:
		static unique<TimerManager> timerManager;
		Dictionary<TimerHandle, Timer, TimerHandleHashFunction> m_timers;

	};
}