/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#include "../MultiThreading.hpp"

std::map<String, Thread>	MultiThreading::threads = std::map<String, Thread>();

void
MultiThreading::Wait(const String& threadToWait) noexcept
{
	if (MultiThreading::threads.contains(threadToWait))
	{
		MultiThreading::threads.at(threadToWait).Wait();
		//delete (MultiThreading::threads.at(threadToWait));
		MultiThreading::threads.erase(threadToWait);
	}
}
