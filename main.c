
// https://gpuopen-librariesandsdks.github.io/V-EZ
// https://www.khronos.org/registry/vulkan/specs/1.2/styleguide.html#markup-word-choices
//
// https://gpuopen.com/learn/reducing-vulkan-api-call-overhead
// https://blog.magnum.graphics/hacking/simple-efficient-vulkan-loading-with-flextgl


#include "00_Common.h"                // <-- Includes required for everything
#include "01_Window.h"                // <-- GLFW window, context, keyboard, mouse
#include "02_VulkanInstance.h"        // <-- Initialize V-EZ Vulkan
#include "03_PhysicalDevice.h"        // <-- Find/Create GPU Device and setup your selected device
#include "04_SwapChain.h"             // <-- Initialize Swap-Chain
#include "05_RenderPass.h"            // <-- Create Render Pass

/*
#include "06_CommandBuffer.h"         // <-- (Section 6.7)  Create Command Pool/Buffer
#include "07_VertexBuffer.h"          // <-- (Section 6.10) Vertex Data/Buffer
#include "08_ShaderandUniforms.h"     // <-- (Section 6.11) Load/Setup Shaders
#include "09_Descriptors.h"           // <-- (Section 6.13) Setup Descriptors/Sets
#include "10_Pipeline.h"             // <-- (Section 6.14) Pipeline
#include "11_RenderLoop.h"           // <-- (Section 6.16) Render Loop


https://www.glfw.org/docs/latest/intro.html#error_handling

https://gist.github.com/bl4ckb0ne/92906f3b00531396a61eaf2966676b16
https://github.com/SaschaWillems/Vulkan/blob/master/base/vulkanexamplebase.cpp

https://github.com/apg360/glfw_vulkan_triangle/blob/master/triangle-vulkan.c
https://github.com/apg360/glfw_vulkan_triangle/blob/master/libs/GLAD/vulkan.h

https://github.com/apg360/Hello_Triangle/blob/master/src/HelloTriangle.cpp
https://github.com/apg360/VulkanTutorial_hello_triangle/blob/master/main.cxx

*/

struct global_parameters VulkanKore_param;

VkResult result;

int cleanup();
//# -----------------------------------------------------
//      Put together all pieces and start Vulkan
//# -----------------------------------------------------
int main(int argc, char *argv[]) {
	
    // Step 1 - Initializing the window
    VulkanKore_param.windowSizeWidth  = 800;
    VulkanKore_param.windowSizeHeight = 600;
    result = SetupWindow(&VulkanKore_param);
    if ( result == EXIT_FAILURE ) {
        dlg_fatal( "Failed to open GLFW window.\n" );
        return EXIT_FAILURE;
    }
    
    // Step 2 - Initialize Vulkan
    VulkanKore_param.instance 	= VK_NULL_HANDLE;
    VulkanKore_param.surface  	= VK_NULL_HANDLE;
    VulkanKore_param.enabled_extension_count 	= 0;
    VulkanKore_param.enabled_layer_count 		= 0;
    VulkanKore_param.enableValidationLayers		= false;
    result = SetupVulkanInstance(&VulkanKore_param);
    if ( result == EXIT_FAILURE ) {
        dlg_fatal( "Failed to initialize Vulkan instance.\n" );
        return EXIT_FAILURE;
    }
    
    // Step 3 - Find/Create GPU Device and setup your selected device
    VulkanKore_param.physicalDevice		 = VK_NULL_HANDLE;
    VulkanKore_param.device				 = VK_NULL_HANDLE;
    VulkanKore_param.physicalDeviceCount = 0;
    result = SetupPhysicalDevice(&VulkanKore_param);
    if ( result == EXIT_FAILURE ) {
        dlg_fatal( "Failed to setup GPU.\n" );
        return EXIT_FAILURE;
    }
    
    // Step 4 - Initialize Swap-Chain
    VulkanKore_param.swapchain			= VK_NULL_HANDLE;
    result = SetupSwapChain(&VulkanKore_param);
    if ( result == EXIT_FAILURE ) {
        dlg_fatal( "Failed to Initialize Swap-Chain.\n" );
        return EXIT_FAILURE;
    }
    
	 // Step 5 - Create Render Pass
     result = SetupRenderPass(&VulkanKore_param);
     if ( result == EXIT_FAILURE ) {
         dlg_fatal( "Failed to Initialize Render Pass.\n" );
         return EXIT_FAILURE;
     }

/*
     // Step 6 - Create Command Pool/Buffer  (Section 6.7)
     VkCommandBuffer  commandBuffer         = NULL;
     SetupCommandBuffer(device,
                        physicalDevice,
                        &commandBuffer);

     // Step 7 - Vertex Data/Buffer          (Section 6.10)
     VkBuffer  vertexInputBuffer            = NULL;
     int       vertexSize                   = 0;
     int       numberOfTriangles            = 0;
     SetupVertexBuffer(device,
                       physicalDevice,
                       &vertexSize,
                       &numberOfTriangles,
                       &vertexInputBuffer);

     // Step 8 - Load/Setup Shaders          (Section 6.11)
     VkShaderModule    vertShaderModule     = NULL;
     VkShaderModule    fragShaderModule     = NULL;
     VkBuffer          buffer               = NULL;
     VkDeviceMemory    memory               = NULL;
     SetupShaderandUniforms(device,
                            physicalDevice,
                            width,
                            height,
                            &vertShaderModule,
                            &fragShaderModule,
                            &buffer,
                            &memory);

// Step 9 - Setup Descriptors/Sets
// Not required in V-EZ

     // Step 10 - Pipeline                   (Section 6.14)
     VkPipeline       pipeline                    = NULL;
     VkPipelineLayout pipelineLayout              = NULL;
     SetupPipeline(device,
                   width,
                   height,
                   vertexSize,
                   descriptorSetLayout,
                   vertShaderModule,
                   fragShaderModule,
                   renderPass,
                   &pipeline,
                   &pipelineLayout);

*/
////////////////////
//----------------------
     // Step 11 - Render Loop
     //glfwMakeContextCurrent(windowHandle); // Make the window's context current, We do not use OpenGL, this is not required
     while ( !glfwWindowShouldClose(VulkanKore_param.windowHandle) )
     {
        // Render here and Keep running
        showFPS(); //Calculate frames per second
        
        //Swap front and back buffers, waits for the monitor to synchronize to prevent tearing
        //You can't display more frames to the user than your monitor's refresh rate anyway, which is probably 60Hz, giving approx 17ms between frames.
        //glfwSwapBuffers(windowHandle); // Cannot swap buffers of a window that has no OpenGL or OpenGL ES context
        
        //Processing events, normally done each frame after buffer swapping.
        //Will use event polling, which processes only those events that have already been received and then returns immediately.
        //This is the best choice when rendering continually, like most games do.
        glfwPollEvents(); // Poll for and process events
        
        //Render the screen
        /*RenderLoop(device,
                   width,
                   height,
                   numberOfTriangles,
                   swapChain,
                   commandBuffer,
                   presentImages,
                   frameBuffers,
                   renderPass,
                   vertexInputBuffer,
                   descriptorSet,
                   pipelineLayout,
                   pipeline);*/
         
     }// End while(..)

//______________________
//The Cleanup  (for every "malloc" there must be a "free"
	result = cleanup();
	if (vk_error != EXIT_SUCCESS) return EXIT_FAILURE;
	
// End
    return EXIT_SUCCESS;
}//End WinMain(..)


int cleanup() {
	
	vezDestroyDevice(VulkanKore_param.device);
	
	//The window surface must be destroyed before the specified Vulkan instance. It is the responsibility of the caller to destroy the window surface.
	//GLFW does not destroy it for you. Call vkDestroySurfaceKHR to destroy the surface.
	//https://www.glfw.org/docs/latest/group__vulkan.html#ga1a24536bec3f80b08ead18e28e6ae965
	vkDestroySurfaceKHR(VulkanKore_param.instance, VulkanKore_param.surface, NULL);
	
    vezDestroyInstance(VulkanKore_param.instance);
	
    glfwDestroyWindow(VulkanKore_param.windowHandle);
    glfwTerminate();
    
    return EXIT_SUCCESS;
}
