
#pragma once // include guard

//# -----------------------------------------------------
// Step 2 - Initialize Vulkan
//
//________//________// START
//Variables and Functions before main function of this step
VkResult vk_error;
struct global_parameters * local_VulkanKore_param;
VezApplicationInfo      appInfo             = {};
VezInstanceCreateInfo   instanceCreateInfo  = {};

//________//________// END

int SetupVulkanExtensions();
int SetupVulkanLayers();

int SetupVulkanInstance(struct global_parameters *pVulkanKore_param)
{
    local_VulkanKore_param=pVulkanKore_param;
    
    appInfo.pApplicationName                    = "VulkanKore";
    appInfo.applicationVersion                  = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName                         = "VulkanKore";
    appInfo.engineVersion                       = VK_MAKE_VERSION(1, 0, 0);
    
    instanceCreateInfo.pApplicationInfo         = &appInfo;
    vk_error = SetupVulkanExtensions();
    if (vk_error != EXIT_SUCCESS) return EXIT_FAILURE;
    vk_error = SetupVulkanLayers();
    if (vk_error != EXIT_SUCCESS) return EXIT_FAILURE;
    
    vk_error = vezCreateInstance(&instanceCreateInfo, &local_VulkanKore_param->instance);
    if (vk_error != VK_SUCCESS) return EXIT_FAILURE;
    
    vk_error = glfwCreateWindowSurface(local_VulkanKore_param->instance, local_VulkanKore_param->windowHandle, NULL, &local_VulkanKore_param->surface);
    if (vk_error != EXIT_SUCCESS) return EXIT_FAILURE;
    
    //--//--//--//
    //Cleanup (for every "malloc" there must be a "free"
    
    return EXIT_SUCCESS;
}// END SetupVulkanInstance()

int SetupVulkanExtensions() {
    //Initialize and reset to default value
    local_VulkanKore_param->enabled_extension_count = 0;
    uint32_t required_extension_count = 0;
    
    // *test = array of character, **test = array of string, 2-dimensional array of characters
    // array of string,  **enabledExtensions = *enabledExtensions[2]
    //variable char*   = string                         => char *y = "ABC";
    //variable char**  = string pointer / string array	=> char **y = {"ABC", "DEF", "GHI", 123};
    
    // Automatically check and list the required extensions for this Vulkan instance to start
    const char **required_extensions = glfwGetRequiredInstanceExtensions(&required_extension_count);
    
    array_copy(required_extension_count, required_extensions, local_VulkanKore_param->enabledExtensions);
    local_VulkanKore_param->enabled_extension_count = required_extension_count;
    
    dlg_info("count no : %u",COUNT_ARRAY_ELEMS( local_VulkanKore_param->enabledExtensions ));
    
    //List the enabled extensions to log file
	log_array_list_item(local_VulkanKore_param->enabled_extension_count,local_VulkanKore_param->enabledExtensions,"Extensions Enabled");
    
    //
    instanceCreateInfo.enabledExtensionCount           = COUNT_ARRAY_ELEMS(local_VulkanKore_param->enabledExtensions);
    instanceCreateInfo.ppEnabledExtensionNames         = local_VulkanKore_param->enabledExtensions;
    
    return EXIT_SUCCESS;
}

int SetupVulkanLayers() {
    //
    // VK_LAYER_KHRONOS_validation or VK_LAYER_LUNARG_standard_validation or "VK_LAYER_NV_optimus"
    local_VulkanKore_param->enabledLayers[0] = "VK_LAYER_LUNARG_standard_validation";
    
    local_VulkanKore_param->enabled_layer_count = 1;
    //local_VulkanKore_param->enabled_layer_count = COUNT_ARRAY_ELEMS(local_VulkanKore_param->enabledLayers);
    
    
    //List the enabled Layers to log file
    //log_array_list_item(local_VulkanKore_param->enabled_layer_count,local_VulkanKore_param->enabledLayers,"Layers enabled");
    
    //
    instanceCreateInfo.ppEnabledLayerNames = local_VulkanKore_param->enabledLayers;
    
    return EXIT_SUCCESS;
}
