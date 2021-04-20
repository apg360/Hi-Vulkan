
#pragma once // include guard

//Note that to avoid symbol conflicts, you have to make sure all translation units in your application include volk.h instead of vulkan.h, 
//  or that you define VK_NO_PROTOTYPES project-wide to make sure you aren’t accidentally picking up symbols from the real Vulkan loader. 
#define VK_NO_PROTOTYPES

// Vulkan backtrace error

#define ENABLE_VULKAN_DEBUG_CALLBACK
// If you instead want to include the Vulkan header from a custom location
// Or use your own custom Vulkan header then do this before the GLFW header.
// => https://www.glfw.org/docs/3.2/vulkan.html
#include <volk.h>

//V-EZ
#include <VEZ.h>


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

