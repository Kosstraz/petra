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

#ifndef PETRA_VVCOMMANDMANAGER_HPP
#define PETRA_VVCOMMANDMANAGER_HPP

# include <vulkan/vulkan.h>
# include <nsl.h>
# include "VVQueue.hpp"
# include "../platform.h"

struct VVCommandManager
{
public:
	VVCommandManager(VkDevice* vkDevice, VVQueue queue, enum VkCommandPoolCreateFlagBits flag = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

	FORCEINLINE
	~VVCommandManager(void)
	{
		if (!isDestroyed)
			this->Destroy();
	}

	void
	Destroy(void);

public:
	bool						isDestroyed;
	VkDevice*					vdevice;
	VkCommandPool				pool;
	VkCommandBuffer				buffers;
	VkCommandBufferBeginInfo	beginInfo;
	//VkCommandBufferAllocateInfo	allocateInfo;
};

#endif
