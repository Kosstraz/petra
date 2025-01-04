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

#ifndef PETRA_VVENUS_HPP
#define PETRA_VVENUS_HPP

# define VVENUS_BAD_PDEVICE_SCORE	-9999

# include <vulkan/vulkan.h>
# include "../colors.h"

struct VVenus
{
	static void
	Init(const char* engineName, unsigned int major, unsigned int minor, unsigned int patch);

	static void
	Destroy(void);

	static void
	ShowPhysicalDevicesProperties(unsigned int i);

	static void
	ShowPhysicalDevicesFeatures(unsigned int i);

	static VkInstance				vk;
	static VkDebugUtilsMessengerEXT	vkDebug;
	static VkPhysicalDevice*		vkPhysicalDevices;
	static VkDevice					vkDevice;
	static VkSurfaceKHR				vkSurfaceKHR;
	static VkApplicationInfo		vkAppInfo;
	static unsigned int				physicalDevicesCount;

private:
	static int
	__EvaluateDeviceScore(VkPhysicalDevice);

	static void
	__CreateLogicalDevice(void);

	static void
	__SetupAppInfo(const char* engineName, unsigned int major, unsigned int minor, unsigned int patch);

	static void
	__CreateVulkanInstance(void);

	static void
	__FindGPUs(void);
};

#endif
