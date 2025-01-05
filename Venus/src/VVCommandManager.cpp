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

#include "VVCommandManager.hpp"

class VVQueue;

VVCommandManager::VVCommandManager(VkDevice* vkDevice, VVQueue queue, enum VkCommandPoolCreateFlagBits flag)
	: isDestroyed(false)
{
	VkCommandPoolCreateInfo	vkCommandPoolCInfo;

	this->vdevice = vkDevice;
	vkCommandPoolCInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	vkCommandPoolCInfo.flags = flag;
	vkCommandPoolCInfo.queueFamilyIndex = queue.GetQueueFamilyIndex();
	vkCreateCommandPool(*this->vdevice, &vkCommandPoolCInfo, nullptr, &this->pool);
	this->beginInfo = VkCommandBufferBeginInfo{};
	this->beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
}

void
VVCommandManager::Destroy(void)
{
	if (!this->isDestroyed)
	{
		vkDestroyCommandPool(*this->vdevice, this->pool, nullptr);
		this->vdevice = nullptr;
		this->isDestroyed = true;
	}
}
