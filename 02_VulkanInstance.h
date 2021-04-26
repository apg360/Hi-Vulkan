
#pragma once // include guard

//# -----------------------------------------------------
// Step 2 - Initialize V-EZ Vulkan
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
    uint32_t required_extension_count = 0;
    
    // Automatically check and list the required extensions for this Vulkan instance to start
    const char **required_extensions = glfwGetRequiredInstanceExtensions(&required_extension_count);
    
    // Initialize number of elements in array
    local_VulkanKore_param->enabledExtensions = malloc( sizeof(char*) * required_extension_count );
    
    // Update the global paramaters
    local_VulkanKore_param->enabled_extension_count = required_extension_count;
    local_VulkanKore_param->enabledExtensions 		= required_extensions;
    
    // List elements to log file
	log_array_list_item(local_VulkanKore_param->enabled_extension_count,local_VulkanKore_param->enabledExtensions,"Extensions Enabled");
    
    // Assign to vulkan instance
    instanceCreateInfo.enabledExtensionCount           = local_VulkanKore_param->enabled_extension_count;
    instanceCreateInfo.ppEnabledExtensionNames         = local_VulkanKore_param->enabledExtensions;
    
    return EXIT_SUCCESS;
}

int SetupVulkanLayers() {
    //Initialize and reset to default value
    uint32_t required_layers_count = 0;
    
    //
    //vezEnumerateDeviceLayerProperties
    required_layers_count = 1;
    
    // Initialize number of elements in array
    local_VulkanKore_param->enabledLayers = malloc( sizeof(char*) * required_layers_count );
    
    // VK_LAYER_KHRONOS_validation or VK_LAYER_LUNARG_standard_validation or "VK_LAYER_NV_optimus"
    local_VulkanKore_param->enabledLayers[0] = "VK_LAYER_LUNARG_standard_validation";
    local_VulkanKore_param->enabled_layer_count = required_layers_count;
    
    // List elements to log file
    log_array_list_item(local_VulkanKore_param->enabled_layer_count,local_VulkanKore_param->enabledLayers,"Layers enabled");
    
    // Assign to vulkan instance
    instanceCreateInfo.ppEnabledLayerNames = local_VulkanKore_param->enabledLayers;
    
    return EXIT_SUCCESS;
}
