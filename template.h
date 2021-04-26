
#pragma once // include guard

//# -----------------------------------------------------
// Step 3 - Find/Create GPU Device and setup your selected device
//
//________//________// START
//Variables and Functions before main function of this step
VkResult vk_error;
struct global_parameters * local_VulkanKore_param;

//________//________// END

int SetupPhysicalDevice(struct global_parameters *pVulkanKore_param)
{
	local_VulkanKore_param=pVulkanKore_param;
	
	
	
	//--//--//--//
    //Cleanup (for every "malloc" there must be a "free"
	
	return EXIT_SUCCESS;
}// END SetupPhysicalDevice(..)
