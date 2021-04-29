
#pragma once // include guard

//# -----------------------------------------------------
// Step 3 - Find/Create GPU Device and setup your selected device
//
//________//________// START
//Variables and Functions before main function of this step
VkResult vk_error;
struct global_parameters * local_VulkanKore_param;
VezSwapchainCreateInfo swapchainCreateInfo = {};
//________//________// END

int SetupSwapChain(struct global_parameters *pVulkanKore_param)
{
	local_VulkanKore_param=pVulkanKore_param;
	
	// Create the swapchain.
    swapchainCreateInfo.surface = local_VulkanKore_param->surface;
    swapchainCreateInfo.format = { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    result = vezCreateSwapchain(local_VulkanKore_param->device, &swapchainCreateInfo, &local_VulkanKore_param->swapchain);
    if (result != VK_SUCCESS) return false;
	
	//--//--//--//
    //Cleanup (for every "malloc" there must be a "free"
	
	return EXIT_SUCCESS;
}// END SetupSwapChain(..)
