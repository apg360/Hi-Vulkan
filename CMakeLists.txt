cmake_minimum_required(VERSION 3.18.X)
project(VulkanKore_Project LANGUAGES C)
add_executable(VulkanKore main.c)

#Compile with no optimization and adding debug symbols
set(CMAKE_BUILD_TYPE debug)
#Compile in release mode optimized but adding debug symbols
#set(CMAKE_BUILD_TYPE RelWithDebInfo)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_DEBUG -D__DEBUG -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fPIC -fpermissive -fstack-protector-all")# -Werror")

#https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_C_KNOWN_FEATURES.html
target_compile_features(VulkanKore PRIVATE c_std_11) #Compiler mode is at least C 11.

# -----------------------------------------------------
# (*) brew install glfw3 --HEAD
# (*) LunarG SDK Vulkan

#############################################
#Finding and linking libpthread
#Required by DLG lib => libDLG.a(dlg.c.o): undefined reference to symbol 'pthread_once@@GLIBC_2.2.5'
set(PTHREAD_LIBS "")
include(CheckLibraryExists)
#-- Looking for pthread_once in pthread
check_library_exists(pthread pthread_once "" LIBPTHREAD)
if(LIBPTHREAD)
    list(APPEND PTHREAD_LIBS "pthread")
endif()
target_link_libraries(VulkanKore PUBLIC ${PTHREAD_LIBS})

#############################################

#Finding and linking GLFW3 (windowing, context & input)
find_package(GLFW3 REQUIRED)
if (GLFW3_FOUND)
    message(STATUS "GLFW3 FOUND")
    target_link_libraries(VulkanKore PUBLIC glfw)
endif (GLFW3_FOUND)

#DLG logging static link
add_library(DLG "libs/dlg/include/dlg/dlg.h" "libs/dlg/include/dlg/dlg.hpp" "libs/dlg/include/dlg/output.h" "libs/dlg/src/dlg/dlg.c")
target_link_libraries(VulkanKore PUBLIC DLG)

#Finding and linking Vulkan
#https://cmake.org/cmake/help/latest/module/FindVulkan.html
find_package (Vulkan REQUIRED)
if (Vulkan_FOUND)
    message(STATUS "Vulkan FOUND")
    include_directories(${Vulkan_INCLUDE_DIRS})
    target_link_libraries (VulkanKore PUBLIC ${Vulkan_LIBRARIES})
    message(STATUS "Vulkan_INCLUDE_DIRS : " ${Vulkan_INCLUDE_DIRS})
    message(STATUS "Vulkan_LIBRARIES : " ${Vulkan_LIBRARIES})
endif (Vulkan_FOUND)

# V-EZ
# https://stackoverflow.com/questions/39598323/how-to-properly-link-libraries-with-cmake
# https://stackoverflow.com/questions/49816206/cmake-find-package-specify-path
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
  
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_link_libraries(VulkanKore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/v-ez/prebuilt_release/Manjaro_21.0/x86_64/libVEZ.so)
elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
  target_link_libraries(VulkanKore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/v-ez/prebuilt_release/macOS.BigSur_11.2.3/x86_64/libVEZ.dylib)
endif()

#Volk
# Set a suitable platform define to compile volk with.
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
  message(STATUS "CMAKE_SYSTEM_NAME = Windows, VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR")
  set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
  message(STATUS "CMAKE_SYSTEM_NAME = Linux, VOLK_STATIC_DEFINES VK_USE_PLATFORM_XLIB_KHR")
  set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_XLIB_KHR)
elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
  message(STATUS "CMAKE_SYSTEM_NAME = Darwin, VOLK_STATIC_DEFINES VK_USE_PLATFORM_MACOS_MVK")
  set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_MACOS_MVK)
endif()
add_subdirectory(libs/volk-1.2.140 volk)
target_link_libraries(VulkanKore PUBLIC volk)

# -----------------------------------------------------
target_include_directories(VulkanKore
   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/mathc"        # single header linear algebra for 3D
   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/vector"       # std::vector from C++ to C
   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/dlg/include"  # logging
   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/dlg/src"      # logging
   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/v-ez/Source"  # V-EZ
   )

#Debug with lldb
#lldb build/VulkanKore
#command alias bfl breakpoint set --file %1 --line %2
#bfl main.c 1840
#run next(step over), step (step in), continue
#fr v renderPassBeginInfo   #Show local variables
