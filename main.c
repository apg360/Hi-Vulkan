
// https://gpuopen-librariesandsdks.github.io/V-EZ
// https://www.khronos.org/registry/vulkan/specs/1.2/styleguide.html#markup-word-choices
//
// https://gpuopen.com/learn/reducing-vulkan-api-call-overhead
// https://blog.magnum.graphics/hacking/simple-efficient-vulkan-loading-with-flextgl


#include "00_Common.h"                // <-- Includes required for everything
#include "01_Window.h"                // <-- GLFW window, context, keyboard, mouse
#include "02_VulkanInstance.h"        // <-- Initialize V-EZ Vulkan

/*
#include "03_PhysicalDevice.h"        // <-- (Section 6.4)  Find/Create Device and Set-up your selected device
#include "04_SwapChain.h"             // <-- (Section 6.5)  Initialize Swap-Chain
#include "05_RenderPass.h"            // <-- (Section 6.6)  Create Render Pass
#include "06_CommandBuffer.h"         // <-- (Section 6.7)  Create Command Pool/Buffer
#include "07_VertexBuffer.h"          // <-- (Section 6.10) Vertex Data/Buffer
#include "08_ShaderandUniforms.h"     // <-- (Section 6.11) Load/Setup Shaders
#include "09_Descriptors.h"           // <-- (Section 6.13) Setup Descriptors/Sets
#include "10_Pipeline.h"             // <-- (Section 6.14) Pipeline
#include "11_RenderLoop.h"           // <-- (Section 6.16) Render Loop
*/

struct global_parameters VulkanKore_param;

//# -----------------------------------------------------
//      Put together all pieces and start Vulkan
//# -----------------------------------------------------
int main(int argc, char *argv[]) {
    
	int result;
	
    // Step 1 - Initializing the window
    VulkanKore_param.width  = 800;
    VulkanKore_param.height = 600;
    result = SetupWindow(&VulkanKore_param);
    if ( result == EXIT_FAILURE ) {
        dlg_fatal( "Failed to open GLFW window.\n" );
        return EXIT_FAILURE;
    }
    
    // Step 2 - Initialize Vulkan
    VulkanKore_param.instance = VK_NULL_HANDLE;
    VulkanKore_param.surface  = VK_NULL_HANDLE;
    result = SetupVulkanInstance(&VulkanKore_param);
    if ( result == EXIT_FAILURE ) {
        dlg_fatal( "Failed to initialize Vulkan instance.\n" );
        return EXIT_FAILURE;
    }
    
    /*
    // Step 3 - Find/Create Device and     (Section 6.4)
    //          Set-up your selected device
    VkPhysicalDevice physicalDevice         = NULL;
    VkDevice         device                 = NULL;
    SetupPhysicalDevice(instance,
                        &physicalDevice,
                        &device);

     // Step 4 - Initialize Swap-Chain     (Section 6.5)
     VkSwapchainKHR swapChain               = NULL;
     VkImage*       presentImages           = NULL;
     VkImageView*   presentImageViews       = NULL;
     SetupSwapChain(device,
                    physicalDevice,
                    surface,
                    &width,
                    &height,
                    &swapChain,
                    &presentImages,
                    &presentImageViews);
    
    //dlg_warn("presentImageViews[0] = %p", &presentImageViews[0]); //Debug
    //dlg_warn("presentImageViews[1] = %p", &presentImageViews[1]); //Debug
    
     // Step 5 - Create Render Pass          (Section 6.6)
     VkRenderPass    renderPass             = NULL;
     VkFramebuffer*  frameBuffers           = NULL;
     SetupRenderPass(device,
                     physicalDevice,
                     width,
                     height,
                     presentImageViews,
                     &renderPass,
                     &frameBuffers);

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

     // Step 9 - Setup Descriptors/Sets      (Section 6.13)
     VkDescriptorSet       descriptorSet       = NULL;
     VkDescriptorSetLayout descriptorSetLayout = NULL;
     SetupDescriptors(device,
                      buffer,
                      &descriptorSet,
                      &descriptorSetLayout);

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
//The Cleanup
/*
     //vkDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessenger, NULL);
     vkDestroyDebugReportCallbackEXT(instance, debugReportCallback_Warning, NULL);
     vkDestroyDebugReportCallbackEXT(instance, debugReportCallback_Error, NULL);
     
     //Cleanup (for every "malloc" there must be a "free"
     free(frameBuffers);
     free(renderPass);
     free(frameBuffers);
     free(presentImages);
     free(presentImageViews);

     vezDestroyInstance(instance); //vkDestroyInstance(instance, NULL);
*/
     glfwDestroyWindow(VulkanKore_param.windowHandle);
     glfwTerminate();

// End
    return EXIT_SUCCESS;
}//End WinMain(..)
