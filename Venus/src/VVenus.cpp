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

#include "VVenus.hpp"
#include "egide/egide.h"
#include "../errors.h"
#include "../colors.h"

VkInstance
VVenus::vk = VK_NULL_HANDLE;
VkPhysicalDevice*
VVenus::vkPhysicalDevices = VK_NULL_HANDLE;
VkDevice
VVenus::vkDevice = VK_NULL_HANDLE;
VkXcbSurfaceCreateInfoKHR
VVenus::vkXcbSurfaceInfoKHR = VkXcbSurfaceCreateInfoKHR{};
VkSurfaceKHR
VVenus::vkSurfaceKHR = VK_NULL_HANDLE;
VkApplicationInfo
VVenus::vkAppInfo = VkApplicationInfo{};
VVQueue*
VVenus::vvGraphicsQueue = nullptr;
VVCommandManager*
VVenus::vvCommandManager = nullptr;
unsigned int
VVenus::physicalDevicesCount = 0U;
unsigned int
VVenus::physicalGDeviceIndex = 0U;

void
VVenus::Init(const char* engineName, unsigned int major, unsigned int minor, unsigned int patch)
{
	VVenus::__SetupAppInfo(engineName, major, minor, patch);
	VVenus::__CreateVulkanInstance();
	VVenus::__FindGPUs();
	VVenus::__CreateLogicalDevice();
	VVenus::__XCBSetSurfaceKHR();
	VVenus::__CreateQueueAndLogic();
}

void
VVenus::SetMainWindow(Window* window)
{
	VVenus::vkXcbSurfaceInfoKHR.window = window->GetXcbID();
	if (vkCreateXcbSurfaceKHR(VVenus::vk, &VVenus::vkXcbSurfaceInfoKHR, nullptr, &VVenus::vkSurfaceKHR) != VK_SUCCESS)
		exit(VK_FAILED_TO_CREATE_XCB_SURFACE_KHR);
}

void
VVenus::Destroy(void)
{
	delete(VVenus::vvCommandManager);
	delete(VVenus::vvGraphicsQueue);
	if (VVenus::vkDevice != VK_NULL_HANDLE)
		vkDestroyDevice(VVenus::vkDevice, nullptr);
	if (VVenus::vkSurfaceKHR != VK_NULL_HANDLE)
		vkDestroySurfaceKHR(VVenus::vk, VVenus::vkSurfaceKHR, nullptr);
	if (VVenus::vk != VK_NULL_HANDLE)
		vkDestroyInstance(VVenus::vk, nullptr);
	free(VVenus::vkPhysicalDevices);
}

int
VVenus::__GetFamilyQueueIndex(int flag)
{
	unsigned int				queueFamilyCount = 0;
	VkQueueFamilyProperties*	queueFamilies;

	vkGetPhysicalDeviceQueueFamilyProperties(VVenus::vkPhysicalDevices[VVenus::physicalGDeviceIndex], &queueFamilyCount, nullptr);
	queueFamilies = cast<VkQueueFamilyProperties*>(malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties)));
	vkGetPhysicalDeviceQueueFamilyProperties(VVenus::vkPhysicalDevices[VVenus::physicalGDeviceIndex], &queueFamilyCount, queueFamilies);
	for (unsigned int i = 0 ; i < queueFamilyCount ; ++i)
	{
		if (queueFamilies[i].queueFlags & flag)
		{
			free(queueFamilies);
			return (i);
		}
	}
	free(queueFamilies);
	return (-1);
}

void
VVenus::__CreateQueueAndLogic(void)
{
	int	graphicsFamilyIndex;

	graphicsFamilyIndex = VVenus::__GetFamilyQueueIndex(VK_QUEUE_GRAPHICS_BIT);
	if (graphicsFamilyIndex == -1)
		exit(VK_NO_GRAPHICS_FAMILY_QUEUE_INDEX);
	VVenus::vvGraphicsQueue = new VVQueue(	VVenus::vkDevice,
											graphicsFamilyIndex,
											0);
	VVenus::vvCommandManager = new VVCommandManager(&VVenus::vkDevice, *VVenus::vvGraphicsQueue);
	VVenus::vvGraphicsQueue->Wait();
	VVenus::vvCommandManager->LinkToVVQueue(*VVenus::vvGraphicsQueue, VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
}
 
void
VVenus::__XCBSetSurfaceKHR(void)
{
	VVenus::vkXcbSurfaceInfoKHR.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
	VVenus::vkXcbSurfaceInfoKHR.flags = 0;
	VVenus::vkXcbSurfaceInfoKHR.connection = Venus::xcb;
}

int
VVenus::__EvaluateDeviceScore(VkPhysicalDevice physicalDevice)
{
	VkPhysicalDeviceProperties	pDeviceProperties;
	VkPhysicalDeviceFeatures	pDeviceFeatures;
	int							score = 0;
	size_t						structSize;

	vkGetPhysicalDeviceProperties(physicalDevice, &pDeviceProperties);
	vkGetPhysicalDeviceFeatures(physicalDevice, &pDeviceFeatures);
	if (pDeviceFeatures.geometryShader == VK_FALSE)
		return (VVENUS_BAD_PDEVICE_SCORE);
	structSize = sizeof(pDeviceFeatures);
	const char* data = ptrCast<const char*>(&pDeviceFeatures);
	for (size_t i = 0; i < structSize; i += sizeof(VkBool32))
	{
		VkBool32	field;
		memcpy(&field, &data[i], sizeof(VkBool32));
		if (field == VK_TRUE)
			++score;
	}
	if (pDeviceFeatures.tessellationShader == VK_FALSE)
		score -= 10;
	switch (pDeviceProperties.deviceType)
	{
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			score += 50;
			break ;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			score += 30;
			break ;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			score += 20;
			break ;
		case VK_PHYSICAL_DEVICE_TYPE_CPU:
			score += 10;
			break ;
		default :
			score = VVENUS_BAD_PDEVICE_SCORE;
			break ;
	}
	return (score);
}

unsigned int
VVenus::__EvaluateAllDevicesScore(void)
{
	Pair	scoreIndex = Pair(VVENUS_BAD_PDEVICE_SCORE, 0U);

	for (unsigned int i = 0 ; VVenus::vkPhysicalDevices[i] ; ++i)
	{
		int	scoreTmp = __EvaluateDeviceScore(VVenus::vkPhysicalDevices[i]);
		if (scoreIndex.a < scoreTmp)
		{
			scoreIndex.a = scoreTmp;
			scoreIndex.b = i;
		}
	}
	if (scoreIndex.a == VVENUS_BAD_PDEVICE_SCORE)
		exit (VK_PHYSICAL_DEVICE_DONT_SUPPORT_GEOMETRYSHADER);
	return (scoreIndex.b);
}

void
VVenus::__CreateLogicalDevice(void)
{
	VkDeviceQueueCreateInfo	vkDeviceQueueCInfo{};
	VkDeviceCreateInfo		vkDeviceCInfo{};
	float					queuePriority = 1.0f;

	vkDeviceQueueCInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	vkDeviceQueueCInfo.queueFamilyIndex = 0;
	vkDeviceQueueCInfo.queueCount = 1;
	vkDeviceQueueCInfo.pQueuePriorities = &queuePriority;

	vkDeviceCInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	vkDeviceCInfo.queueCreateInfoCount = 1;
	vkDeviceCInfo.pQueueCreateInfos = &vkDeviceQueueCInfo;
	VVenus::physicalGDeviceIndex = VVenus::__EvaluateAllDevicesScore();
	if (vkCreateDevice(VVenus::vkPhysicalDevices[VVenus::physicalGDeviceIndex], &vkDeviceCInfo, nullptr, &VVenus::vkDevice) != VK_SUCCESS)
		exit(VK_FAILED_TO_CREATE_LOGICAL_DEVICE);
	
	//ShowPhysicalDevicesProperties(VVenus::physicalDeviceUsedIndex);
	//ShowPhysicalDevicesFeatures(VVenus::physicalDeviceUsedIndex);
}

void
VVenus::__FindGPUs(void)
{
	vkEnumeratePhysicalDevices(VVenus::vk, &VVenus::physicalDevicesCount, nullptr);
	if (VVenus::physicalDevicesCount == 0)
		exit(VK_NOT_FOUND_PHYSICAL_DEVICE);
	VVenus::vkPhysicalDevices = cast<VkPhysicalDevice*>(calloc(127, sizeof(VkPhysicalDevice)));
	vkEnumeratePhysicalDevices(VVenus::vk, &VVenus::physicalDevicesCount, VVenus::vkPhysicalDevices);
}

void
VVenus::__SetInstanceExtension(VkInstanceCreateInfo* vkInstCInfo)
{
	constexpr unsigned int	extensionCount = 2;
	const char** const		extensions = cast<const char**>(malloc(sizeof(const char*) * extensionCount)); // to free after uses

	extensions[0] = VK_KHR_SURFACE_EXTENSION_NAME;
	extensions[1] = VK_KHR_XCB_SURFACE_EXTENSION_NAME;
	vkInstCInfo->enabledExtensionCount = extensionCount;
	vkInstCInfo->ppEnabledExtensionNames = extensions;
}

void
VVenus::__CreateVulkanInstance(void)
{
	VkInstanceCreateInfo	vkCreateIInfo{};

	//const char* const		khronos = strdup("VK_LAYER_KHRONOS_validation");

	vkCreateIInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vkCreateIInfo.pApplicationInfo = &VVenus::vkAppInfo;
	VVenus::__SetInstanceExtension(&vkCreateIInfo);
	if (vkCreateInstance(&vkCreateIInfo, nullptr, &VVenus::vk) != VK_SUCCESS)
		exit(VK_FAILED_TO_CREATE_AN_INSTANCE);
}

void
VVenus::__SetupAppInfo(const char* engineName, unsigned int major, unsigned int minor, unsigned int patch)
{
	VVenus::vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	VVenus::vkAppInfo.pApplicationName = "VVenus";
	VVenus::vkAppInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	VVenus::vkAppInfo.pEngineName = engineName;
	VVenus::vkAppInfo.engineVersion = VK_MAKE_VERSION(major, minor, patch);
	VVenus::vkAppInfo.apiVersion = VK_API_VERSION_1_3;
}

void
VVenus::ShowPhysicalDevicesProperties(unsigned int i)
{
	VkPhysicalDeviceProperties	pDeviceProperties;

	vkGetPhysicalDeviceProperties(VVenus::vkPhysicalDevices[i], &pDeviceProperties);
	std::cout << BOLD << "Device[" << i << "] Properties :" << RESET << std::endl;
	std::cout << CYAN << "API version = " << BOLD << pDeviceProperties.apiVersion << RESET << std::endl;
	std::cout << CYAN << "Device ID = " << BOLD << pDeviceProperties.deviceID << RESET << std::endl;
	std::cout << CYAN << "Device name = " << BOLD << pDeviceProperties.deviceName << RESET << std::endl;
	std::cout << CYAN << "Driver version = " << BOLD << pDeviceProperties.driverVersion << RESET << std::endl;
	std::cout << CYAN << "Device is a " << BLUE << BOLD;
	switch (pDeviceProperties.deviceType)
	{
		case VK_PHYSICAL_DEVICE_TYPE_CPU:
			std::cout << "CPU";
			break ;
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			std::cout << "discrete GPU";
			break ;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			std::cout << "integrated GPU";
			break ;
		case VK_PHYSICAL_DEVICE_TYPE_OTHER:
			std::cout << "\"other\"";
			break ;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			std::cout << "virtual GPU";
			break ;
		default:
			std::cout << "??not referenced??";
			break ;
	}
	std::cout << RESET << std::endl;
	std::cout << CYAN << "Pipeline cache UUID = " << BOLD << pDeviceProperties.pipelineCacheUUID << RESET << std::endl;
	std::cout << CYAN << "Vendor ID = " << BOLD << pDeviceProperties.vendorID << RESET << std::endl;
	std::cout << std::endl;
}

std::ostream&
ShowBoolInOstream(std::ostream& os, const char* text, bool b)
{
	os << CYAN << text << BOLD;
	if (b)
		return (os << GREEN << "true" << RESET << std::endl);
	return (os << RED << "false" << RESET << std::endl);
}

void
VVenus::ShowPhysicalDevicesFeatures(unsigned int i)
{
	VkPhysicalDeviceFeatures	pDeviceFeatures;

	vkGetPhysicalDeviceFeatures(VVenus::vkPhysicalDevices[i], &pDeviceFeatures);
	std::cout << BOLD << "Device[" << i << "] Features supported :" << RESET << std::endl;
	ShowBoolInOstream(std::cout, "alphaToOne = ", pDeviceFeatures.alphaToOne);
	ShowBoolInOstream(std::cout, "depthBiasClamp = ", pDeviceFeatures.depthBiasClamp);
	ShowBoolInOstream(std::cout, "depthBounds = ", pDeviceFeatures.depthBounds);
	ShowBoolInOstream(std::cout, "depthClamp = ", pDeviceFeatures.depthClamp);
	ShowBoolInOstream(std::cout, "drawIndirectFirstInstance = ", pDeviceFeatures.drawIndirectFirstInstance);
	ShowBoolInOstream(std::cout, "dualSrcBlend = ", pDeviceFeatures.dualSrcBlend);
	ShowBoolInOstream(std::cout, "fillModeNonSolid = ", pDeviceFeatures.fillModeNonSolid);
	ShowBoolInOstream(std::cout, "fragmentStoresAndAtomics = ", pDeviceFeatures.fragmentStoresAndAtomics);
	ShowBoolInOstream(std::cout, "fullDrawIndexUint32 = ", pDeviceFeatures.fullDrawIndexUint32);
	ShowBoolInOstream(std::cout, "geometryShader = ", pDeviceFeatures.geometryShader);
	ShowBoolInOstream(std::cout, "imageCubeArray = ", pDeviceFeatures.imageCubeArray);
	ShowBoolInOstream(std::cout, "independentBlend = ", pDeviceFeatures.independentBlend);
	ShowBoolInOstream(std::cout, "inheritedQueries = ", pDeviceFeatures.inheritedQueries);
	ShowBoolInOstream(std::cout, "largePoints = ", pDeviceFeatures.largePoints);
	ShowBoolInOstream(std::cout, "logicOp = ", pDeviceFeatures.logicOp);
	ShowBoolInOstream(std::cout, "multiDrawIndirect = ", pDeviceFeatures.multiDrawIndirect);
	ShowBoolInOstream(std::cout, "multiViewport = ", pDeviceFeatures.multiViewport);
	ShowBoolInOstream(std::cout, "occlusionQueryPrecise = ", pDeviceFeatures.occlusionQueryPrecise);
	ShowBoolInOstream(std::cout, "pipelineStatisticsQuery = ", pDeviceFeatures.pipelineStatisticsQuery);
	ShowBoolInOstream(std::cout, "robustBufferAccess = ", pDeviceFeatures.robustBufferAccess);
	ShowBoolInOstream(std::cout, "samplerAnisotropy = ", pDeviceFeatures.samplerAnisotropy);
	ShowBoolInOstream(std::cout, "sampleRateShading = ", pDeviceFeatures.sampleRateShading);
	ShowBoolInOstream(std::cout, "shaderClipDistance = ", pDeviceFeatures.shaderClipDistance);
	ShowBoolInOstream(std::cout, "shaderCullDistance = ", pDeviceFeatures.shaderCullDistance);
	ShowBoolInOstream(std::cout, "shaderFloat64 = ", pDeviceFeatures.shaderFloat64);
	ShowBoolInOstream(std::cout, "shaderImageGatherExtended = ", pDeviceFeatures.shaderImageGatherExtended);
	ShowBoolInOstream(std::cout, "shaderInt16 = ", pDeviceFeatures.shaderInt16);
	ShowBoolInOstream(std::cout, "shaderInt64 = ", pDeviceFeatures.shaderInt64);
	ShowBoolInOstream(std::cout, "shaderResourceMinLod = ", pDeviceFeatures.shaderResourceMinLod);
	ShowBoolInOstream(std::cout, "shaderResourceResidency = ", pDeviceFeatures.shaderResourceResidency);
	ShowBoolInOstream(std::cout, "shaderSampledImageArrayDynamicIndexing = ", pDeviceFeatures.shaderSampledImageArrayDynamicIndexing);
	ShowBoolInOstream(std::cout, "shaderStorageBufferArrayDynamicIndexing = ", pDeviceFeatures.shaderStorageBufferArrayDynamicIndexing);
	ShowBoolInOstream(std::cout, "shaderStorageImageArrayDynamicIndexing = ", pDeviceFeatures.shaderStorageImageArrayDynamicIndexing);
	ShowBoolInOstream(std::cout, "shaderStorageImageExtendedFormats = ", pDeviceFeatures.shaderStorageImageExtendedFormats);
	ShowBoolInOstream(std::cout, "shaderStorageImageMultisample = ", pDeviceFeatures.shaderStorageImageMultisample);
	ShowBoolInOstream(std::cout, "shaderStorageImageReadWithoutFormat = ", pDeviceFeatures.shaderStorageImageReadWithoutFormat);
	ShowBoolInOstream(std::cout, "shaderStorageImageWriteWithoutFormat = ", pDeviceFeatures.shaderStorageImageWriteWithoutFormat);
	ShowBoolInOstream(std::cout, "shaderTessellationAndGeometryPointSize = ", pDeviceFeatures.shaderTessellationAndGeometryPointSize);
	ShowBoolInOstream(std::cout, "shaderUniformBufferArrayDynamicIndexing = ", pDeviceFeatures.shaderUniformBufferArrayDynamicIndexing);
	ShowBoolInOstream(std::cout, "sparseBinding = ", pDeviceFeatures.sparseBinding);
	ShowBoolInOstream(std::cout, "sparseResidency2Samples = ", pDeviceFeatures.sparseResidency2Samples);
	ShowBoolInOstream(std::cout, "sparseResidency4Samples = ", pDeviceFeatures.sparseResidency4Samples);
	ShowBoolInOstream(std::cout, "sparseResidency8Samples = ", pDeviceFeatures.sparseResidency8Samples);
	ShowBoolInOstream(std::cout, "sparseResidency16Samples = ", pDeviceFeatures.sparseResidency16Samples);
	ShowBoolInOstream(std::cout, "sparseResidencyAliased = ", pDeviceFeatures.sparseResidencyAliased);
	ShowBoolInOstream(std::cout, "sparseResidencyBuffer = ", pDeviceFeatures.sparseResidencyBuffer);
	ShowBoolInOstream(std::cout, "sparseResidencyImage2D = ", pDeviceFeatures.sparseResidencyImage2D);
	ShowBoolInOstream(std::cout, "sparseResidencyImage3D = ", pDeviceFeatures.sparseResidencyImage3D);
	ShowBoolInOstream(std::cout, "tessellationShader = ", pDeviceFeatures.tessellationShader);
	ShowBoolInOstream(std::cout, "textureCompressionASTC_LDR = ", pDeviceFeatures.textureCompressionASTC_LDR);
	ShowBoolInOstream(std::cout, "textureCompressionBC = ", pDeviceFeatures.textureCompressionBC);
	ShowBoolInOstream(std::cout, "textureCompressionETC2 = ", pDeviceFeatures.textureCompressionETC2);
	ShowBoolInOstream(std::cout, "variableMultisampleRate = ", pDeviceFeatures.variableMultisampleRate);
	ShowBoolInOstream(std::cout, "vertexPipelineStoresAndAtomics = ", pDeviceFeatures.vertexPipelineStoresAndAtomics);
	ShowBoolInOstream(std::cout, "wideLines = ", pDeviceFeatures.wideLines);
	std::cout << std::endl;
}

