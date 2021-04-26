
#pragma once // include guard

#include <stdio.h>
#include <stdlib.h>     // EXIT_FAILURE, EXIT_SUCCESS
#include <assert.h>     // C++ DBG_ASSERT become assert
#include <string.h>     // strcpy, strcmp, strcat(concatenates), etc...
#include <dlg/dlg.h>    // logging
#include <mathc.h>      // single header library for 3D linear algebra; MATHC is a simple math library for 2D and 3D programming.

//#include <vector.h>   // std::vector from C++ to C --> "${CMAKE_CURRENT_SOURCE_DIR}/libs/vector"
//#include "libs/vector_typed_list/vector.h"


/*  * JUST FOR INFORMATION *

	=> VOLK  #define VK_USE_PLATFORM_MACOS_MVK
	
	The VK_USE_PLATFORM_*_KHR macros do not need to be defined for the Vulkan part of GLFW to work.
	Define them only if you are using these extensions directly.
	https://www.glfw.org/docs/latest/vulkan_guide.html
	
	#if defined(VK_USE_PLATFORM_WIN32_KHR)
	#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
	#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	#define GLFW_EXPOSE_NATIVE_WAYLAND
	#include <wayland-client.h>
	#elif defined(VK_USE_PLATFORM_XCB_KHR)
	#define GLFW_EXPOSE_NATIVE_X11
	#include <X11/Xlib-xcb.h>
	#elif defined(VK_USE_PLATFORM_XLIB_KHR)
	#define GLFW_EXPOSE_NATIVE_X11
	#include <X11/Xlib.h>
	#elif defined(VK_USE_PLATFORM_IOS_MVK)
	#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	#endif

	// Cannot use GLFW "glfwCreateWindowSurface" because "GLFW_INCLUDE_NONE", no OpenGL header
	// Window surface is created by vulkan, we use VOLK for that

	// WINDOWS => defined(VK_KHR_win32_surface)
	#if defined(VK_KHR_win32_surface)
	extern PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
	extern PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR;
	#endif
	// macOS => defined(VK_MVK_macos_surface)
	#if defined(VK_MVK_macos_surface)
	extern PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK;
	#endif
	// Linux => defined(VK_KHR_xcb_surface)
	// X11: Vulkan instance with VK_KHR_xcb_surface extension
	#if defined(VK_KHR_xcb_surface)
	extern PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
	extern PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR;
	#endif
	// Linux => defined(VK_KHR_xlib_surface)
	// X11: Vulkan instance with VK_KHR_xlib_surface extension
	#if defined(VK_KHR_xlib_surface)
	extern PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
	extern PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR;
	#endif

	// GLFW window API macros
	#define GLFW_EXPOSE_NATIVE_WIN32 // glfwGetWin32Window (GLFWwindow *window)
	#define GLFW_EXPOSE_NATIVE_COCOA // glfwGetCocoaWindow (GLFWwindow *window)
	#define GLFW_EXPOSE_NATIVE_X11   // glfwGetX11Window (GLFWwindow *window)
	#include <GLFW/glfw3native.h>   // https://www.glfw.org/docs/3.0/group__native.html
	// GLFW context API macros
	//#define GLFW_EXPOSE_NATIVE_GLX   // glfwGetGLXContext (GLFWwindow *window)

 ******* ******* ******* ******* */

//________//________// //________//________// //________//________//
//
// Note that to avoid symbol conflicts, you have to make sure all translation units in your application include volk.h instead of vulkan.h, 
//   or that you define VK_NO_PROTOTYPES project-wide to make sure you aren’t accidentally picking up symbols from the real Vulkan loader. 
#define VK_NO_PROTOTYPES

// Vulkan backtrace error
#define ENABLE_VULKAN_DEBUG_CALLBACK

/*
	=> #define GLFW_INCLUDE_VULKAN
	By default, GLFW will look for the Vulkan loader on demand at runtime via its standard name (vulkan-1.dll on Windows, libvulkan.so.1 on Linux 
	and other Unix-like systems and libvulkan.1.dylib on macOS).
	This means that GLFW does not need to be linked against the loader.
	However, it also means that if you are using the static library form of the Vulkan loader GLFW will either fail to find it or (worse) use the wrong one.
	
	=> Custom loader VOLK
	If you instead want to include the Vulkan header from a custom location or use your own custom Vulkan header then do this before the GLFW header.
	
	https://www.glfw.org/docs/latest/vulkan_guide.html
	https://www.glfw.org/docs/3.2/vulkan.html
*/

#include <volk.h>
// GLFW
#define GLFW_INCLUDE_NONE // include no OpenGL header
#include <GLFW/glfw3.h>
//________//________// //________//________// //________//________//

//V-EZ
#include <VEZ.h>

//________//________// //________//________// //________//________//

// This is a universal formula to find number of elements present in an array
//   it will work for arrays of all data types such as int, char, float etc.
// We must use define instead of a function. Because An array sent as a parameter to a function is treated as a pointer, 
//   so sizeof will return the pointer's size, instead of the array's. : void printSizeOf(int intArray[])
#define COUNT_ARRAY_ELEMS(x) (int) (  sizeof(x) / sizeof((x)[0])  )
	/*if ( sizeof((x)[0]) != NULL ) {								\
		(int) (  sizeof(x) / sizeof((x)[0])  )		\
	}*/

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

//List all array items
#define array_copy(count, array_source, array_dest)         \
    for ( uint32_t index=0; index < count; index++) {		\
        (array_dest)[index] = (array_source)[index];		\
    }

//List all array items
#define log_array_list_item(count, array, msg)             \
    dlg_info("%s count %u",msg,count);			            \
    for (uint32_t index = 0;  index < count;  index++)		\
    {														\
        dlg_info("%s no %u : %s",msg,index,array[index]);	\
    }

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

// https://stackoverflow.com/questions/6169972/realloc-an-array-of-structs
/*int growArray(User **user_array, int currentSize, int numNewElems)
{
    const int totalSize = currentSize + numNewElems;
    User *temp = (User*)realloc(*user_array, (totalSize * sizeof(User)));

    if (temp == NULL)
    {
        printf("Cannot allocate more memory.\n");
        return 0;
    }
    else
    {
        *user_array = temp;
    }

    return totalSize;
}*/

/*
// https://stackoverflow.com/questions/3536153/c-dynamically-growing-array/3536261
// https://stackoverflow.com/questions/26831981/should-i-check-if-malloc-was-successful
// http://www.cplusplus.com/reference/cstdlib/realloc
// https://overiq.com/c-programming-101/the-realloc-function-in-c
Array a;

initArray(&a, 5);  // initially 5 elements
for (int i = 0; i < 100; i++)
  insertArray(&a, i);  // automatically resizes as necessary
printf("%d\n", a.array[9]);  // print 10th element
printf("%d\n", a.used);  // print number of elements
freeArray(&a);
*/
typedef struct {
  int *array;
  size_t used;
  size_t size;
} myArray;

void initArray(myArray *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(myArray *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(myArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}


typedef struct Array {
  int capacity;  	// How many elements can this array hold?
  int count;  		// How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} myArray2;

myArray2 *create_array (int capacity);
void arr_append(struct Array *arr, char *element);



//-------------------------------
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
    const char *enabledExtensions[2];
    
    uint32_t enabled_layer_count;
    const char *enabledLayers[1];
};
