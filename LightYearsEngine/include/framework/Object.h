#pragma once

namespace ly
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		void Destroy();
		bool IsPendingDestroy() const { return m_isPendingDestroy; }

	private:
		bool m_isPendingDestroy;
	};
}