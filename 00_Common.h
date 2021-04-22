
#pragma once // include guard

#include <stdio.h>
#include <stdlib.h>     // EXIT_FAILURE, EXIT_SUCCESS
#include <assert.h>     // C++ DBG_ASSERT become assert
#include <string.h>     // strcpy, strcmp, strcat(concatenates), etc...
#include <dlg/dlg.h>    // logging
#include <mathc.h>      // single header library for 3D linear algebra; MATHC is a simple math library for 2D and 3D programming.

//#include <vector.h>   // std::vector from C++ to C --> "${CMAKE_CURRENT_SOURCE_DIR}/libs/vector"
//#include "libs/vector_typed_list/vector.h"


//________//________// //________//________// //________//________// 
#define GLFW_INCLUDE_NONE // include no OpenGL header

// GLFW window API macros
//#define GLFW_EXPOSE_NATIVE_WIN32 // glfwGetWin32Window (GLFWwindow *window)
//#define GLFW_EXPOSE_NATIVE_COCOA // glfwGetCocoaWindow (GLFWwindow *window)
//#define GLFW_EXPOSE_NATIVE_X11 // glfwGetX11Window (GLFWwindow *window)

// GLFW context API macros
//#define GLFW_EXPOSE_NATIVE_GLX // glfwGetGLXContext (GLFWwindow *window)

//GLFW
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h> // https://www.glfw.org/docs/3.0/group__native.html
//________//________// //________//________// //________//________// 

// Note that to avoid symbol conflicts, you have to make sure all translation units in your application include volk.h instead of vulkan.h, 
//   or that you define VK_NO_PROTOTYPES project-wide to make sure you aren’t accidentally picking up symbols from the real Vulkan loader. 
#define VK_NO_PROTOTYPES

// Vulkan backtrace error

#define ENABLE_VULKAN_DEBUG_CALLBACK
// If you instead want to include the Vulkan header from a custom location
// Or use your own custom Vulkan header then do this before the GLFW header.
// => https://www.glfw.org/docs/3.2/vulkan.html
//#include <volk.h>

//V-EZ
#include <VEZ.h>
//________//________// //________//________// //________//________// 

struct global_parameters {
    int		width;
    int		height;
	GLFWwindow* windowHandle;
	VkInstance instance;
	VkSurfaceKHR surface;
	//VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	//VkDevice device 				= VK_NULL_HANDLE;
	//VezSwapchain swapchain 			= VK_NULL_HANDLE;
    uint32_t enabled_extension_count;
    uint32_t enabled_layer_count;
    const char *enabledExtensions[64];
    const char *enabledLayers[64];
};

// This is a universal formula to find number of elements present in an array
//   it will work for arrays of all data types such as int, char, float etc.
// We must use define instead of a function. Because An array sent as a parameter to a function is treated as a pointer, 
//   so sizeof will return the pointer's size, instead of the array's. : void printSizeOf(int intArray[])
#define COUNT_ARRAY_ELEMS(x) (int) (sizeof(x) / sizeof((x)[0]))

//Check vulkan error and exit application
#define ERR_VULKAN_EXIT(val, err_msg)               \
    if ( val != VK_SUCCESS ) {                      \
        dlg_fatal(err_msg);                         \
        fflush(stdout);                             \
        exit(1);                                    \
    }

/*//Assert value and exit application
#define ERR_ASSERT_EXIT(val1, val2, err_msg)    \
    if ( !( assert(val1 == val2) ) ) {                     \
        dlg_fatal(err_msg);                                \
        fflush(stdout);                                    \
        assert(false);                                     \
    }
*/

//Error and exit application
#define ERR_EXIT(err_msg)                           \
    do {                                            \
        dlg_fatal(err_msg);                         \
        fflush(stdout);                             \
        exit(1);                                    \
    } while (0)

/*
    dlg_warn("This is a warning. If on a console, it will be printed yellow");
    dlg_error("Errors are red. Colors work even on windows consoles");
    dlg_info("Another feature: Utf-8 printing works automatically, even for שׁǐŉďốẅś consoles");
    dlg_fatal("This one is printed bold. For more information, read the example already");
    dlg_assertm(1 == 2, "Well, this assertion will probably %s...", "fail");
    dlg_infot(("tag1", "tag2"), "We can tag our stuff. Can be used to filter/redirect messages");
    dlg_asserttm(("tag3"), 3 == 2, "The same goes for asserts");
*/

int fps_nbFrames = 0;
double fps_lastTime = 0;
void showFPS()
{
     // Measure speed
     //char title_string[256];
     //title_string [255] = 'VulkanKore';
     
     double currentTime = glfwGetTime();
     double delta = currentTime - fps_lastTime;
     fps_nbFrames++;
     
     if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
         
         //dlg_warn("currentTime: %.1f",currentTime);
         //dlg_warn("lastTime: %.1f",lastTime);
         //dlg_warn("delta: %.1f",delta);
         //dlg_warn("nbFrames: %u",nbFrames);
         //dlg_warn("nbFrames/delta: %.1f",nbFrames/delta);
         
         double fps = (double) fps_nbFrames/delta;
         dlg_info("FPS : %.1f",fps);
         
         //cout << 1000.0/double(nbFrames) << endl;
         //std::stringstream ss;
         //ss << GAME_NAME << " " << VERSION << " [" << fps << " FPS]";
         
         //snprintf ( title, 255, "%s %s - [FPS: %3.2f]",
         //             GAME_NAME, VERSION, 1000.0f / (float)nbFrames );
                   
         //glfwSetWindowTitle(windowHandle, ss.str().c_str());
         //glfwSetWindowTitle(windowHandle, title_string);
         
         fps_nbFrames = 0;
         fps_lastTime = currentTime;
     }
     //assert(false);
}
