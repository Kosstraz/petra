/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#include "../Thread.hpp"

pthread_t
Thread_MainThreadID = pthread_self();
thread_local
const int32
Thread::ThisTID = gettid();

Thread::~Thread()
{}

#include <iostream>
bool
Thread::IsAlive()
{
	if (joined)
		return (false);
	else if (pthread_tryjoin_np(this->thread, nullptr) == EBUSY)
		return (true);
	return (false);
}

void
Thread::TryStop()
{
	pthread_cancel(this->thread);
	pthread_join(this->thread, nullptr);
	this->joined = true;
}

const char*
Thread::IsStillAliveException::what() const noexcept
{
	return ("The thread is still alive!");
}
