#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
	Object::Object()
		:m_isPendingDestroy{false}
	{
	}

	Object::~Object()
	{
		LOG("Object destroyed")
	}

	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		m_isPendingDestroy = true;
	}

	weak<Object> Object::GetWeakRef()
	{
		return weak_from_this();
	}

	weak<const Object> Object::GetWeakRef() const
	{
		return weak_from_this();
	}
}