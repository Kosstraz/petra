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

#ifndef VENUS_VVCOMMANDMANAGER_HPP
#define VENUS_VVCOMMANDMANAGER_HPP

# include <vulkan/vulkan.h>
# include "../errors.h"
# include "egide/egide.h"
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

// All the queue in the commandPool will be destroyed and be re-created.
// If any things have be submitted in, reconsidere to wait the queue
	void
	LinkToVVQueue(VVQueue queue, enum VkCommandPoolCreateFlagBits flag);

	FORCEINLINE
	void
	ResetBuffer(void)
	{
		vkResetCommandBuffer(this->buffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
	}

	FORCEINLINE
	void
	ResetPool(void)
	{
		//vkResetCommandPool(this->vdevice, this->pool, VkCommandPoolResetFlagsBits::)
	}

// Start recording for vulkan commands
	FORCEINLINE
	void
	BeginRecord(void)
	{
		vkBeginCommandBuffer(this->buffer, &this->beginInfo);
	}

// Add a vulkan command when VVCommandManager is recording
	template <typename TFun, typename... TArgs>
	FORCEINLINE
	void
	AddCommand(TFun&& vkCmdFun, TArgs&&... pArgs)
	{
		vkCmdFun(this->buffer, Meta::Forward<TArgs>(pArgs)...);
	}

// End recording for vulkan commands
	FORCEINLINE
	void
	EndRecord(void)
	{
		vkEndCommandBuffer(this->buffer);
	}

public:
	bool						isDestroyed;
	VkDevice*					vdevice;
	VkCommandPool				pool;
	VkCommandBuffer				buffer;
	VkCommandBufferBeginInfo	beginInfo;
	//VkCommandBufferAllocateInfo	allocateInfo;
};

#endif
