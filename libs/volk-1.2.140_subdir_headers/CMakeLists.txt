
cmake_minimum_required(VERSION 3.18.2 FATAL_ERROR)

#CMAKE community FAQ https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#how-do-i-use-a-different-compiler
#CMAKE useful variables : https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables
message("$ENV{PATH}")
set(ENV{HELLO} "World")
message("$ENV{HELLO}")

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

project(helloProject LANGUAGES CXX)

add_executable(Hello main.cxx)

# Include volk as part of the build tree to make the target known.
# The two-argument version of add_subdirectory allows adding non-subdirs.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/volk-1.2.140 volk)

target_compile_features(Hello PRIVATE cxx_std_17)

target_link_libraries(Hello PRIVATE volk_headers)
#target_link_libraries(Hello PRIVATE volk::volk_headers)

# -----------------------------------------------------
#Not required anymore
#
#https://cmake.org/cmake/help/latest/command/set_property.html
#https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
#Default C++ is 14, we need to set it explicitly to 17
#set_property(TARGET Hello PROPERTY CXX_STANDARD 17)
#
#set(CMAKE_CXX_STANDARD 17)
