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

#ifndef VENUS_VVQUEUE_HPP
#define VENUS_VVQUEUE_HPP

# define VVQUEUE_TRY_TO_SUBMIT_WHEN_NO_CB	1

# include <vulkan/vulkan.h>
# include "egide/egide.h"
# include "../platform.h"

class VVCommandBuffer;

class VVQueue final
{
public:
	VVQueue(VkDevice device, int pQueueFamilyIndex, unsigned int pQueueIndex);
	~VVQueue(void) = default;

// Add a commandBuffer to the whitelist
// The whitelist is all the buffers who will be added to the queue
	void
	AddCommandBuffer(VkCommandBuffer pCommandBuffer);

// Get the queue family index
	FORCEINLINE
	int
	GetQueueFamilyIndex(void)
	{
		return (this->queueFamilyIndex);
	}

// Get the raw vulkan queue
	FORCEINLINE
	VkQueue
	GetVkQueue(void)
	{
		return (this->queue);
	}

// Wait until the queue is empty.
	FORCEINLINE
	VkResult
	Wait(void)
	{
		return (vkQueueWaitIdle(this->queue));
	}

// Submit all the buffers (in whitelist) to the queue
	FORCEINLINE
	VkResult
	Submit(void)
	{
		if (this->commandBuffers->Size() == 0U)
			return (cast<VkResult>(VVQUEUE_TRY_TO_SUBMIT_WHEN_NO_CB));
		return (vkQueueSubmit(this->queue, this->elementCount, &this->submitInfo, nullptr));
	}

private:
	SmartPtr<Queue<VkCommandBuffer>>
							commandBuffers;
	VkQueue					queue;
	VkSubmitInfo			submitInfo;
	unsigned int			queueIndex;
	int						queueFamilyIndex;
	int						deviceUsedIndex;
	int						elementCount;
	bool					isDestroyed;
};

#endif
