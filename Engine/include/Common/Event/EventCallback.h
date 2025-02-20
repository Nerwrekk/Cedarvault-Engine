#pragma once

#include "Events/Events.h"

namespace cedar
{
	class IEventCallback
	{
	public:
		virtual ~IEventCallback() = default;

		void Exectue(IEvent& e)
		{
			Call(e);
		}

	private:
		virtual void Call(IEvent& e) = 0;
	};

	template <typename TOwner, typename TEvent>
	class EventCallBack : public IEventCallback
	{
	public:
		typedef void (*FreeCallbackFunction)(TEvent&);
		typedef void (TOwner::*MemberCallbackFunction)(TEvent&);

		EventCallBack(TOwner* owner, MemberCallbackFunction callbackFunction)
		{
			this->m_ownerInst = owner;
			this->m_memberCallbackfunction = callbackFunction;

			this->m_freeCallbackFunction = nullptr;
		}

		EventCallBack(FreeCallbackFunction freeCallbackFunction)
		{
			this->m_freeCallbackFunction = freeCallbackFunction;

			this->m_ownerInst = nullptr;
			this->m_memberCallbackfunction = nullptr;
		}

		virtual ~EventCallBack() override = default;

	private:
		TOwner* m_ownerInst;
		MemberCallbackFunction m_memberCallbackfunction;

		FreeCallbackFunction m_freeCallbackFunction;

		virtual void Call(IEvent& e) override
		{
			if (m_memberCallbackfunction)
			{
				std::invoke(m_memberCallbackfunction, m_ownerInst, static_cast<TEvent&>(e));
			}
			else if (m_freeCallbackFunction)
			{
				std::invoke(m_freeCallbackFunction, static_cast<TEvent&>(e));
			}
		}
	};
} // namespace cedar