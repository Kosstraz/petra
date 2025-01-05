/************************************************************************** */
/*																			*/
/*		   ▄███████▄    ▄████████     ███        ▄████████    ▄████████		*/
/*		  ███    ███   ███    ███ ▀█████████▄   ███    ███   ███    ███		*/
/*		  ███    ███   ███    █▀     ▀███▀▀██   ███    ███   ███    ███		*/
/*		  ███    ███  ▄███▄▄▄         ███   ▀  ▄███▄▄▄▄██▀   ███    ███		*/
/*		▀█████████▀  ▀▀███▀▀▀         ███     ▀▀███▀▀▀▀▀   ▀███████████		*/
/*		  ███          ███    █▄      ███     ▀███████████   ███    ███		*/
/*		  ███          ███    ███     ███       ███    ███   ███    ███		*/
/*		 ▄████▀        ██████████    ▄████▀     ███    ███   ███    █▀ 		*/
/*                                              ███    ███              	*/
/*																			*/
/************************************************************************** */

#include "VVQueue.hpp"

VVQueue::VVQueue(VkDevice device, int pQueueFamilyIndex, unsigned int pQueueIndex) : deviceUsedIndex(0), elementCount(0), isDestroyed(false)
{
	this->submitInfo = VkSubmitInfo{};
	this->submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	this->queueFamilyIndex = pQueueFamilyIndex;
	this->queueIndex = pQueueIndex;
	vkGetDeviceQueue(device, this->queueFamilyIndex, this->queueIndex, &this->queue);
}

void
VVQueue::AddCommandBuffer(VkCommandBuffer pCommandBuffer)
{
	this->commandBuffers->Push(pCommandBuffer);
	this->submitInfo.pCommandBuffers = commandBuffers->begin().get();
	++this->submitInfo.commandBufferCount;
}
