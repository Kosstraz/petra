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

#ifndef PETRA_VVQUEUE_HPP
#define PETRA_VVQUEUE_HPP

# define VVQUEUE_TRY_TO_SUBMIT_WHEN_NO_CB	1

# include <vulkan/vulkan.h>
# include <nsl.h>
# include "../platform.h"

class VVCommandBuffer;

class VVQueue final
{
public:
	VVQueue(VkDevice device, int pQueueFamilyIndex, unsigned int pQueueIndex);
	~VVQueue(void) = default;

	void
	AddCommandBuffer(VkCommandBuffer pCommandBuffer);

	FORCEINLINE
	int
	GetQueueFamilyIndex(void)
	{
		return (this->queueFamilyIndex);
	}

	FORCEINLINE
	VkQueue
	GetVkQueue(void)
	{
		return (this->queue);
	}

	FORCEINLINE
	VkResult
	Wait(void)
	{
		return (vkQueueWaitIdle(this->queue));
	}

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
