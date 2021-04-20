
#pragma once // include guard

//# -----------------------------------------------------
// Step 2 - Initialize Vulkan
//
//________//________// START
//Variables and Functions before main function of this step

//________//________// END

void SetupVulkanInstance()
{
    
	VezApplicationInfo		appInfo     		= {};
    appInfo.pApplicationName 					= "VulkanKore";
    appInfo.applicationVersion 					= VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName 						= "VulkanKore";
    appinfo.engineVersion 						= VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion                  		= VK_API_VERSION_1_2;
	
	VezInstanceCreateInfo	instanceCreateInfo  = {};
	createInfo.pApplicationInfo         		= &appInfo;
	
	VkResult result = vezCreateInstance(&instanceCreateInfo, &instance);
	if (result != VK_SUCCESS) return false;
    
	// Create a surface to render to.
	result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
	if (result != VK_SUCCESS) return false;
	
    //--//--//--//
	//Cleanup (for every "malloc" there must be a "free"
    
}// END SetupVulkanInstance()

