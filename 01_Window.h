
#pragma once // include guard

//# -----------------------------------------------------
// Step 1 - GLFW window, context, keyboard, mouse

//________//________// 
// Definition Variables and Functions before main function of this step
// Most events are reported through callbacks, whether it's a key being pressed, 
//          a GLFW window being moved, or an error occurring.
void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
    dlg_error("Error: %s\n", description);
}
//________//________// END

int SetupWindow(struct global_parameters *pVulkanKore_param)
{
    //Callback functions must be set, so GLFW knows to call them. 
    glfwSetErrorCallback(glfw_error_callback);
    
    /*
    TODO
    
    glfwSetWindowUserPointer(demo->window, demo);
    glfwSetWindowRefreshCallback(demo->window, demo_refresh_callback);
    glfwSetFramebufferSizeCallback(demo->window, demo_resize_callback);
    glfwSetKeyCallback(demo->window, demo_key_callback);
    */
    
    // Initialise GLFW
    if( !glfwInit() )
    {
        dlg_fatal("Failed to initialize GLFW");
        return EXIT_FAILURE;
    }
    
    // Unless you will be using OpenGL or OpenGL ES with the same window as Vulkan, there is no need to create a context.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //disable context creation
    // Window Hints  https://www.glfw.org/docs/latest/window_guide.html#window_hints_x11
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    // Use GLFW to create a window
    pVulkanKore_param->windowHandle = glfwCreateWindow(pVulkanKore_param->width, pVulkanKore_param->height, "Vulkan window", NULL, NULL);
    if (pVulkanKore_param->windowHandle == NULL )
    {
      dlg_fatal("GLFW failed to create window");
      glfwTerminate();
      return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

