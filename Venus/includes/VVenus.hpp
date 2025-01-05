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

# ifndef cast
#  define cast		static_cast
# endif
# ifndef ptrCast
#  define ptrCast	reinterpret_cast
# endif
# ifndef polyCast
#  define polyCast	dynamic_cast
# endif
# ifndef constCast
#  define constCast	const_cast
# endif

# define VVENUS_BAD_PDEVICE_SCORE	-9999

# define VK_USE_PLATFORM_XCB_KHR
# include <vulkan/vulkan.h>
# include <vulkan/vulkan_xcb.h>
# include <nsl.h>
# include "Venus.hpp"
# include "Window.hpp"
# include "../colors.h"
# include "VVCommandManager.hpp"
# include "VVQueue.hpp"

struct VVenus final : private Venus
{
	static void
	Init(const char* engineName, unsigned int major, unsigned int minor, unsigned int patch);

	static void
	SetMainWindow(Window* window);

	static void
	Destroy(void);

	static void
	ShowPhysicalDevicesProperties(unsigned int i);

	static void
	ShowPhysicalDevicesFeatures(unsigned int i);

	static VkInstance					vk;
	static VkPhysicalDevice*			vkPhysicalDevices;
	static VkDevice						vkDevice;
	static VkApplicationInfo			vkAppInfo;
	static VkSurfaceKHR					vkSurfaceKHR;
	static VkXcbSurfaceCreateInfoKHR	vkXcbSurfaceInfoKHR;
	static VVCommandManager*			vvCommandManager;
	static VVQueue*						vvGraphicsQueue;
	//static VVQueue						vvComputeQueue
	//static VVQueue						vvTransfertQueue;
	static unsigned int					physicalDevicesCount;
	static unsigned int					physicalGDeviceIndex;

private:
	static int
	__GetFamilyQueueIndex(int flag);

	static void
	__CreateQueueAndLogic(void);

	static void
	__SetInstanceExtension(VkInstanceCreateInfo*);

	static void
	__XCBSetSurfaceKHR(void);

	static int
	__EvaluateDeviceScore(VkPhysicalDevice);

	static unsigned int
	__EvaluateAllDevicesScore(void);

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
