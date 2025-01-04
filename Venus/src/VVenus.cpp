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
#include <nsl.h>
#include "../errors.h"
#include "../colors.h"

VkInstance
VVenus::vk = VK_NULL_HANDLE;
VkDebugUtilsMessengerEXT
VVenus::vkDebug = VK_NULL_HANDLE;
VkPhysicalDevice*
VVenus::vkPhysicalDevices = VK_NULL_HANDLE;
VkDevice
VVenus::vkDevice = VK_NULL_HANDLE;
VkSurfaceKHR
VVenus::vkSurfaceKHR = VK_NULL_HANDLE;
VkApplicationInfo
VVenus::vkAppInfo = VkApplicationInfo{};
unsigned int
VVenus::physicalDevicesCount = 0;

void
VVenus::Init(const char* engineName, unsigned int major, unsigned int minor, unsigned int patch)
{
	VVenus::__SetupAppInfo(engineName, major, minor, patch);
	VVenus::__CreateVulkanInstance();
	VVenus::__FindGPUs();
	VVenus::__CreateLogicalDevice();
}

void
VVenus::Destroy(void)
{
	if (VVenus::vkDevice != VK_NULL_HANDLE)
		vkDestroyDevice(VVenus::vkDevice, nullptr);
	if (VVenus::vkSurfaceKHR != VK_NULL_HANDLE)
		vkDestroySurfaceKHR(VVenus::vk, VVenus::vkSurfaceKHR, nullptr);
	//if (VVenus::vkDebug != VK_NULL_HANDLE)
	//	vkDestroyDebugUtilsMessengerEXT(VVenus::vk, VVenus::vkDebug, nullptr);
	if (VVenus::vk != VK_NULL_HANDLE)
		vkDestroyInstance(VVenus::vk, nullptr);
	free(VVenus::vkPhysicalDevices);
}

int
VVenus::__EvaluateDeviceScore(VkPhysicalDevice physicalDevice)
{
	VkPhysicalDeviceProperties	pDeviceProperties;
	VkPhysicalDeviceFeatures	pDeviceFeatures;
	int							score = 0;

	vkGetPhysicalDeviceProperties(physicalDevice, &pDeviceProperties);
	vkGetPhysicalDeviceFeatures(physicalDevice, &pDeviceFeatures);
	if (pDeviceFeatures.geometryShader == false)
		return (VVENUS_BAD_PDEVICE_SCORE);
// Taille de la structure VkPhysicalDeviceFeatures
    size_t size = sizeof(pDeviceFeatures);

    // Pointeur vers la mémoire brute de la structure
    const uint8_t* data = reinterpret_cast<const uint8_t*>(&pDeviceFeatures);

    // Parcourir chaque champ, ici supposé que chaque champ booléen occupe 4 octets (comme VkBool32)
    for (size_t i = 0; i < size; i += sizeof(VkBool32)) {
        VkBool32 field;
        std::memcpy(&field, &data[i], sizeof(VkBool32));  // Copie de 4 octets dans un VkBool32
        
        // Si le champ booléen est true, incrémente le score
        if (field == VK_TRUE) {
            ++score;
        }
    }

    std::cout << "Score: " << score << std::endl;
}

void
VVenus::__CreateLogicalDevice(void)
{
	VkDeviceQueueCreateInfo	vkDeviceQueueCInfo{};
	VkDeviceCreateInfo		vkDeviceCInfo{};
	Pair					scoreIndex = Pair(VVENUS_BAD_PDEVICE_SCORE, 0U);
	float					queuePriority = 1.0f;

	vkDeviceQueueCInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	vkDeviceQueueCInfo.queueFamilyIndex = 0;
	vkDeviceQueueCInfo.queueCount = 1;
	vkDeviceQueueCInfo.pQueuePriorities = &queuePriority;

	vkDeviceCInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	vkDeviceCInfo.queueCreateInfoCount = 1;
	vkDeviceCInfo.pQueueCreateInfos = &vkDeviceQueueCInfo;

	for (unsigned int i = 0 ; VVenus::vkPhysicalDevices[i] ; ++i)
		if (scoreIndex.a < __EvaluateDeviceScore(VVenus::vkPhysicalDevices[i]))
			scoreIndex.b = i;
	if (scoreIndex.a == VVENUS_BAD_PDEVICE_SCORE)
		exit (VK_PHYSICAL_DEVICE_DONT_SUPPORT_GEOMETRYSHADER);
	else if (vkCreateDevice(VVenus::vkPhysicalDevices[scoreIndex.b], &vkDeviceCInfo, nullptr, &VVenus::vkDevice) != VK_SUCCESS)
		exit(VK_FAILED_TO_CREATE_LOGICAL_DEVICE);
	
	//ShowPhysicalDevicesProperties(scoreIndex.b);
	//ShowPhysicalDevicesFeatures(scoreIndex.b);
}

void
VVenus::__FindGPUs(void)
{
	vkEnumeratePhysicalDevices(VVenus::vk, &VVenus::physicalDevicesCount, nullptr);
	if (VVenus::physicalDevicesCount == 0)
		exit(VK_NOT_FOUND_PHYSICAL_DEVICE);
	VVenus::vkPhysicalDevices = static_cast<VkPhysicalDevice*>(calloc(127, sizeof(VkPhysicalDevice)));
	vkEnumeratePhysicalDevices(VVenus::vk, &VVenus::physicalDevicesCount, VVenus::vkPhysicalDevices);
}

void
VVenus::__CreateVulkanInstance(void)
{
	VkInstanceCreateInfo	vkCreateIInfo{};
	//Queue<const char*>		validationLayers;

	//validationLayers.Push("VK_LAYER_KHRONOS_validation");
	vkCreateIInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vkCreateIInfo.pApplicationInfo = &VVenus::vkAppInfo;
	//vkCreateIInfo.enabledLayerCount = static_cast<unsigned int>(validationLayers.Size());
	//vkCreateIInfo.ppEnabledLayerNames = validationLayers.begin().get();
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

