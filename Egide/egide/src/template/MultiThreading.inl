/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_MULTITHREADING_INL
#define EGIDE_MULTITHREADING_INL

# include "../MultiThreading.hpp"

template <typename TRet>
TRet
MultiThreading::Get(const String& threadToWait) noexcept
{
	return (MultiThreading::threads.at(threadToWait).Get<TRet>());
}

template <typename TRet>
TRet
MultiThreading::TryGet(const String& threadToWait)
{
	try
	{
		return (MultiThreading::threads.at(threadToWait).TryGet<TRet>());
	}
	catch (Thread::IsStillAliveException& e)
	{
		throw (e);
	}
	catch (...)
	{
		throw (std::exception());
	}
}

template <typename TFun>
void
MultiThreading::Create(String pThreadID, TFun pFun)
{
	if (MultiThreading::threads.contains(pThreadID))
		throw (MultiThreading::ThreadIDAlreadyUsed());
	MultiThreading::threads.emplace(pThreadID, Thread(pFun));
	if (!pFun)
		std::cout << "null" << std::endl;
	else
		std::cout << "valide" << std::endl;
}

template <typename TFun, typename... TArgs>
void
MultiThreading::Create(String pThreadID, TFun pFun, TArgs&&... pArgs)
{
	std::cout << "Create\n";
	if (MultiThreading::threads.contains(pThreadID))
		throw (MultiThreading::ThreadIDAlreadyUsed());
	MultiThreading::threads.emplace(pThreadID, Thread(pFun, Meta::Forward<TArgs>(pArgs)...));
}

template <typename TRet, class CObject, typename... TFunArgs, typename... TArgs>
void
MultiThreading::Create(String pThreadID, TRet (CObject::*pFun)(TFunArgs...), CObject* pObject, TArgs&&... pArgs)
{
	if (MultiThreading::threads.contains(pThreadID))
		throw (MultiThreading::ThreadIDAlreadyUsed());
	MultiThreading::threads.emplace(pThreadID, Thread(pFun, pObject, Meta::Forward<TArgs>(pArgs)...));
}

template <typename TRet, class CObject>
void
MultiThreading::Create(String pThreadID, TRet (CObject::*pFun)(void), CObject* pObject)
{
	if (MultiThreading::threads.contains(pThreadID))
		throw (MultiThreading::ThreadIDAlreadyUsed());
	MultiThreading::threads.emplace(pThreadID, Thread(pFun, pObject));
}

FORCEINLINE bool
MultiThreading::IsAlive(const String& threadName) noexcept
{
	return (MultiThreading::__isAlive__(threadName));
}

FORCEINLINE bool
MultiThreading::IsExist(const String& threadName) noexcept
{
	return (MultiThreading::__isExist__(threadName));
}

FORCEINLINE bool
MultiThreading::IsAlive(String&& threadName) noexcept
{
	return (MultiThreading::__isAlive__(Meta::Move(threadName)));
}

FORCEINLINE bool
MultiThreading::IsExist(String&& threadName) noexcept
{
	return (MultiThreading::__isExist__(Meta::Move(threadName)));
}

FORCEINLINE bool
MultiThreading::__isAlive__(String&& threadName) noexcept
{
	if (MultiThreading::threads.contains(Meta::Move(threadName)))
		if (MultiThreading::threads.at(Meta::Move(threadName)).IsAlive())
			return (true);
	return (false);
}

FORCEINLINE bool
MultiThreading::__isAlive__(const String& threadName) noexcept
{
	if (MultiThreading::threads.contains(Meta::Move(threadName)))
		if (MultiThreading::threads.at(Meta::Move(threadName)).IsAlive())
			return (true);
	return (false);
}

FORCEINLINE bool
MultiThreading::__isExist__(String&& threadName) noexcept
{
	return (MultiThreading::threads.contains(Meta::Move(threadName)));
}

FORCEINLINE bool
MultiThreading::__isExist__(const String& threadName) noexcept
{
	return (MultiThreading::threads.contains(Meta::Move(threadName)));
}

#endif
