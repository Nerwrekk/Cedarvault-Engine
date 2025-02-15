#pragma once

#include "Events/Events.h"

namespace cedar
{
	class IEventCallback
	{
	public:
		virtual ~IEventCallback() = default;

		void Exectue(Event& e)
		{
			Call(e);
		}

	private:
		virtual void Call(Event&) = 0;
	};

	template <typename TOwner, typename TEvent>
	class EventCallBack : public IEventCallback
	{
	public:
		EventCallBack(TOwner* owner, CallbackFunction callbackFunction)
		{
			this->m_ownerInst = owner;
			this->m_callbackfunction = callbackFunction;
		}

		virtual ~EventCallBack() override = default;

	private:
		typedef void (TOwner::*CallbackFunction)(TEvent&);
		TOwner* m_ownerInst;
		CallbackFunction m_callbackfunction;

		virtual void Call(Event&) override
		{
			std::invoke(m_callbackfunction, m_ownerInst, static_cast<TEvent&>(e));
		}
	};
} // namespace cedar