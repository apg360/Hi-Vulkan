#!/bin/zsh

# Tested on macOS BigSur 11.2.3
#
#Pre-requisite, must be installed in the system :
# (*) builtin preinstalled macOS llvm 11.0.0
# (*) Cmake 3.19.1
# (*) Ninja 1.10.2
# (*) Vulkan SDK from LunarG,  1.2.148
# (*) GLFW 3.3.4
# (*) Command_Line_Tools_for_Xcode_12.4.dmg
#     If that doesn't show you any updates, run: sudo rm -rf /Library/Developer/CommandLineTools && sudo xcode-select --install
#     Alternatively, manually download them from: https://developer.apple.com/download/more/.

export PATH=~/MyProjects/Ninja1.10.2/ninja:$PATH
export CC=clang
export CXX=clang++
export SDKROOT='/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk'
export CPATH='/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk:/opt/local/include'
export LIBRARY_PATH='/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib:/opt/local/lib'
export CFLAGS='-g -O0'

#Use cmake to perform OS operation
cmake -E rm -rf build           #delete directory build
cmake -E make_directory build   #create directory build

#Generator
#Use Ninja as generator on the CMakeLists in current directory, and generate under directory 'build'
cmake -E time cmake -G Ninja . -B build

#Use cmake to build
#ninja -j 4 -C build
cmake -E time cmake --build build
#"-DCMAKE_C_FLAGS:STRING=-g -O0"

#rm vert.spv frag.spv
#glslangValidator -V simple.frag
#glslangValidator -V simple.vert
#cp vert.spv frag.spv build/

#Run application if it exists (will exist if was compiled successfully)
executableFileName=VulkanKore
if [ -f build/$executableFileName ]; then
        echo -e "\n********* STARTING ********\n"
        build/./$executableFileName
else 
    echo -e "\nERROR: Compilation failed, $executableFileName does not exist.\n"
fi
echo -e "\n\n"