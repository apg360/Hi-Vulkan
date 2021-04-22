
#pragma once // include guard

//# -----------------------------------------------------
// Step 2 - Initialize Vulkan
//
//________//________// START
//Variables and Functions before main function of this step

//________//________// END

int SetupVulkanInstance(struct global_parameters *pVulkanKore_param)
{
    VkResult result;
    
	VezApplicationInfo		appInfo     		= {};
    appInfo.pApplicationName 					= "VulkanKore";
    appInfo.applicationVersion 					= VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName 						= "VulkanKore";
    appInfo.engineVersion 						= VK_MAKE_VERSION(1, 0, 0);
	
	VezInstanceCreateInfo	instanceCreateInfo  = {};
	instanceCreateInfo.pApplicationInfo         = &appInfo;
	
	result = vezCreateInstance(&instanceCreateInfo, &pVulkanKore_param->instance);
	if (result != VK_SUCCESS) return EXIT_FAILURE;
    
	// Create a surface to render to
	result = glfwCreateWindowSurface(pVulkanKore_param->instance, pVulkanKore_param->windowHandle, NULL, &pVulkanKore_param->surface);
	if (result != VK_SUCCESS) return EXIT_FAILURE;
	
    //--//--//--//
	//Cleanup (for every "malloc" there must be a "free"
    
    return EXIT_SUCCESS;
}// END SetupVulkanInstance()

int SetupExtensions() {
	// Automatically check and list the required extensions for this Vulkan instance to start
	return EXIT_SUCCESS;
}

int SetupLayers(VezInstanceCreateInfo *pInstanceCreateInfo) {
	const char *enabledLayers[] = { "VK_LAYER_LUNARG_standard_validation" }; // VK_LAYER_KHRONOS_validation or VK_LAYER_LUNARG_standard_validation or "VK_LAYER_NV_optimus"
    pInstanceCreateInfo->enabledLayerCount = COUNT_ARRAY_ELEMS(enabledLayers);
    pInstanceCreateInfo->ppEnabledLayerNames = enabledLayers;
    
	return EXIT_SUCCESS;
}
