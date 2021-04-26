
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

int SetupPhysicalDevice(struct global_parameters *pVulkanKore_param)
{
	local_VulkanKore_param=pVulkanKore_param;
	
	vk_error = ScanGPU();
    if (vk_error != EXIT_SUCCESS) return EXIT_FAILURE;
    
    // Create a logical device connection to the physical device.
    deviceCreateInfo.enabledExtensionCount		= 0;
    deviceCreateInfo.ppEnabledExtensionNames	= NULL;
    result = vezCreateDevice(local_VulkanKore_param->physicalDevice, &deviceCreateInfo, &local_VulkanKore_param->device);
    if (vk_error != VK_SUCCESS) return EXIT_FAILURE;
    
	//--//--//--//
    //Cleanup (for every "malloc" there must be a "free"
	
	return EXIT_SUCCESS;
}// END SetupPhysicalDevice(..)

int ScanGPU() {
	// Enumerate and select the first discrete GPU physical device.
    vezEnumeratePhysicalDevices(local_VulkanKore_param->instance, &local_VulkanKore_param->physicalDeviceCount, NULL);
 
    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    vezEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());
 
    for (auto pd : physicalDevices)
    {
        VkPhysicalDeviceProperties properties;
        vezGetPhysicalDeviceProperties(pd, &properties);
        if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            physicalDevice = pd;
            break;
        }
    }
    
    if (physicalDevice == VK_NULL_HANDLE) return EXIT_FAILURE;
        
    return EXIT_SUCCESS;
}
