
#pragma once // include guard

//# -----------------------------------------------------
// Step 3 - Find/Create GPU Device and setup your selected device
//
//________//________// START
//Variables and Functions before main function of this step
VkResult vk_error;
struct global_parameters * local_VulkanKore_param;
VezDeviceCreateInfo		deviceCreateInfo 	= {};
//________//________// END

int ScanGPUs();
int gpuQueue();

int SetupPhysicalDevice(struct global_parameters *pVulkanKore_param)
{
	local_VulkanKore_param=pVulkanKore_param;
	
	vk_error = ScanGPUs();
    if (vk_error != EXIT_SUCCESS) return EXIT_FAILURE;
    
    vk_error = gpuQueue();
    if (vk_error != EXIT_SUCCESS) return EXIT_FAILURE;
    
    // Create a logical device connection to the physical device.
    deviceCreateInfo.enabledExtensionCount		= 0;
    deviceCreateInfo.ppEnabledExtensionNames	= NULL;
    vk_error = vezCreateDevice(local_VulkanKore_param->physicalDevice, &deviceCreateInfo, &local_VulkanKore_param->device);
    if (vk_error != VK_SUCCESS) return EXIT_FAILURE;
    
	//--//--//--//
    //Cleanup (for every "malloc" there must be a "free"
	
	return EXIT_SUCCESS;
}// END SetupPhysicalDevice(..)

int ScanGPUs() {
	// Enumerate GPU physical device
    vk_error = vezEnumeratePhysicalDevices(local_VulkanKore_param->instance, &local_VulkanKore_param->physicalDeviceCount, NULL);
    if(local_VulkanKore_param->physicalDeviceCount == 0) { dlg_error("Couldn't detect any device present with Vulkan support"); return EXIT_FAILURE;} 
    else { dlg_info("GPU device with vulkan support : %u",local_VulkanKore_param->physicalDeviceCount); };
    
    local_VulkanKore_param->physicalDevices = malloc( sizeof(VkPhysicalDevice*) * local_VulkanKore_param->physicalDeviceCount );
    
    vk_error = vezEnumeratePhysicalDevices(local_VulkanKore_param->instance, &local_VulkanKore_param->physicalDeviceCount, local_VulkanKore_param->physicalDevices);
	
	// Enumerate all physical devices and print out the details
	for (uint32_t index = 0; index < local_VulkanKore_param->physicalDeviceCount; ++index)
	{
		VkPhysicalDeviceProperties deviceProperties;
		memset(&deviceProperties, 0, sizeof deviceProperties);
		
		//Gets the properties of a physical device
		vezGetPhysicalDeviceProperties(local_VulkanKore_param->physicalDevices[index], &deviceProperties); 
		
		dlg_info("Driver Version: %d", deviceProperties.driverVersion);
		dlg_info("Device Name:    %s", deviceProperties.deviceName);
		dlg_info("Device Type:    %d", deviceProperties.deviceType);
		dlg_info("API Version:    %d.%d.%d", 
		  (deviceProperties.apiVersion>>22)&0x3FF,
		  (deviceProperties.apiVersion>>12)&0x3FF,
		  (deviceProperties.apiVersion&0xFFF)
		);
		
		// Select the first discrete GPU physical device.
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            local_VulkanKore_param->physicalDevice = local_VulkanKore_param->physicalDevices[index];
            break;
        }
		
	}
	//If no GPU was selected
    // commented TEMPORARY for testing -> if (local_VulkanKore_param->physicalDevice == VK_NULL_HANDLE) {dlg_error("Couldn't select any discrete GPU device"); return EXIT_FAILURE;}
    // 				For testing, if no discrete gpu was found, we force take first gpu. Most likely integrated gpu like intel UHD.
    if (local_VulkanKore_param->physicalDevice == VK_NULL_HANDLE) { local_VulkanKore_param->physicalDevice=local_VulkanKore_param->physicalDevices[0]; }
    
    return EXIT_SUCCESS;
}

int gpuQueue() {
	
	/*
	// Fill up the physical device memory properties:
	VkPhysicalDeviceMemoryProperties memoryProperties;
	vkGetPhysicalDeviceMemoryProperties( *outPhysicalDevice,
										 // handle to the device query
										 &memoryProperties);
										 // pointer to VkPhysicalDeviceMemoryProperties structure returned with properties
	// Here's where you initialize your queues
	// You'll discuss queues next - however, you need to specify the queue
	// details for the device creation info
	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType              = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	// Use the first queue family in the family list
	queueCreateInfo.queueFamilyIndex   = 0;
	queueCreateInfo.queueCount         = 1;
	float queuePriorities[]            = { 1.0f };
	queueCreateInfo.pQueuePriorities   = queuePriorities;
	
	// Same extension you specified when initializing Vulkan
	const char *deviceExtensions[]     = { "VK_KHR_swapchain" };
	const char *layers[]               = { "VK_LAYER_KHRONOS_validation" }; // "VK_LAYER_LUNARG_standard_validation" or "VK_LAYER_NV_optimus"
	*/
	return EXIT_SUCCESS;
}
