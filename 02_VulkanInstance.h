
#pragma once // include guard

//# -----------------------------------------------------
// Step 2 - Initialize Vulkan
//
//________//________// START
//Variables and Functions before main function of this step

//________//________// END

int SetupVulkanInstance(struct global_parameters *VulkanKore_param)
{
    VkResult result;
    
	VezApplicationInfo		appInfo     		= {};
    appInfo.pApplicationName 					= "VulkanKore";
    appInfo.applicationVersion 					= VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName 						= "VulkanKore";
    appInfo.engineVersion 						= VK_MAKE_VERSION(1, 0, 0);
	
	VezInstanceCreateInfo	instanceCreateInfo  = {};
	instanceCreateInfo.pApplicationInfo         = &appInfo;
	
	result = vezCreateInstance(&instanceCreateInfo, &VulkanKore_param->instance);
	if (result != VK_SUCCESS) return EXIT_FAILURE;
    
	// Create a surface to render to
	//result = glfwCreateWindowSurface(VulkanKore_param->instance, VulkanKore_param->windowHandle, NULL, VulkanKore_param->surface);
	//if (result != VK_SUCCESS) return EXIT_FAILURE;
	
    //--//--//--//
	//Cleanup (for every "malloc" there must be a "free"
    
    return EXIT_SUCCESS;
}// END SetupVulkanInstance()

