/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_MULTITHREADING_HPP
#define EGIDE_MULTITHREADING_HPP

# include "Thread.hpp"
# include "String.hpp"
# include <map>

// It's a simpler way to create thread and manage them.
class MultiThreading final
{
public:
	explicit MultiThreading(const MultiThreading&) 	= delete;
	explicit MultiThreading(MultiThreading&&) 		= delete;
	explicit MultiThreading()						= delete;
	virtual ~MultiThreading()						= delete;

	template <typename TFun>
	static void	Create(String pThreadID, TFun pFun);
	template <typename TFun, typename... TArgs>
	static void	Create(String pThreadID, TFun pFun, TArgs&&... PArgs);
	template <typename TRet, class CObject>
	static void	Create(String pThreadID, TRet (CObject::*pFun)(void), CObject* pObject);
	template <typename TRet, class CObject, typename... TFunArgs, typename... TArgs>
	static void	Create(String pThreadID, TRet (CObject::*pFun)(TFunArgs...), CObject* pObject, TArgs&&... PArgs);

	template <typename TRet>
	static TRet	Get(const String& threadToGet) noexcept;
	template <typename TRet>
	static TRet	TryGet(const String& threadToGet);

	static void	Wait(const String& threadToWait) noexcept ;

	static FORCEINLINE bool	IsAlive(const String& threadName) noexcept;
	
	static FORCEINLINE bool	IsExist(const String& threadName) noexcept;

	
	static FORCEINLINE bool	IsAlive(String&& threadName) noexcept;
	
	static FORCEINLINE bool	IsExist(String&& threadName) noexcept;

	struct ThreadIDAlreadyUsed : std::exception { virtual const char* what(void) noexcept { return ("ThreaID is already used!"); }};

private:

	static FORCEINLINE bool	__isAlive__(const String& threadName) noexcept;
	
	static FORCEINLINE bool	__isAlive__(String&& threadName) noexcept;

	static FORCEINLINE bool	__isExist__(const String& threadName) noexcept;
	
	static FORCEINLINE bool	__isExist__(String&& threadName) noexcept;

private:
	static std::map<String, Thread>	threads;
};

# include "template/MultiThreading.inl"
#endif
