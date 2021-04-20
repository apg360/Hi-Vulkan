
#pragma once // include guard

//# -----------------------------------------------------
// Step 1 - Window

//________//________// 
// Definition Variables and Functions before main function of this step
// Most events are reported through callbacks, whether it's a key being pressed, 
//          a GLFW window being moved, or an error occurring.
void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
    dlg_error("Error: %s\n", description);
}

int nbFrames = 0;
double lastTime = 0;
//________//________// END

SetupWindow(struct global_parameters *VulkanKore_param)
{
    //Callback functions must be set, so GLFW knows to call them. 
    glfwSetErrorCallback(glfw_error_callback);
    
    // Initialise GLFW
    if( !glfwInit() )
    {
        dlg_fatal("Failed to initialize GLFW");
        return NULL;
    }
    
    // Unless you will be using OpenGL or OpenGL ES with the same window as Vulkan, there is no need to create a context.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //disable context creation
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    vulkan_kore_app->windowHandle = glfwCreateWindow(VulkanKore_param->width, VulkanKore_param->height, "Vulkan window", NULL, NULL);
    //glfwGetX11Window(windowHandle);
    
    if (!vulkan_kore_app->windowHandle)
    {
      dlg_fatal("GLFW failed to create window");
      glfwTerminate();
      return NULL;
    }
    
    if ( VulkanKore_param->windowHandle == NULL ) {
        printf( "Failed to open GLFW window.\n" );
        glfwTerminate();
        return EXIT_FAILURE;
    }
}

void showFPS()
{
     // Measure speed
     //char title_string[256];
     //title_string [255] = 'VulkanKore';
     
     double currentTime = glfwGetTime();
     double delta = currentTime - lastTime;
     nbFrames++;
     
     if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
         
         //dlg_warn("currentTime: %.1f",currentTime);
         //dlg_warn("lastTime: %.1f",lastTime);
         //dlg_warn("delta: %.1f",delta);
         //dlg_warn("nbFrames: %u",nbFrames);
         //dlg_warn("nbFrames/delta: %.1f",nbFrames/delta);
         
         double fps = (double) nbFrames/delta;
         dlg_info("FPS : %.1f",fps);
         
         //cout << 1000.0/double(nbFrames) << endl;
         //std::stringstream ss;
         //ss << GAME_NAME << " " << VERSION << " [" << fps << " FPS]";
         
         //snprintf ( title, 255, "%s %s - [FPS: %3.2f]",
         //             GAME_NAME, VERSION, 1000.0f / (float)nbFrames );
                   
         //glfwSetWindowTitle(windowHandle, ss.str().c_str());
         //glfwSetWindowTitle(windowHandle, title_string);
         
         nbFrames = 0;
         lastTime = currentTime;
     }
     //assert(false);
}
