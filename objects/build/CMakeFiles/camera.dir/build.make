# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/1409/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1409/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/robert/VSG/shipProject/camera

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robert/VSG/shipProject/camera/build

# Include any dependencies generated for this target.
include CMakeFiles/camera.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/camera.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/camera.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/camera.dir/flags.make

CMakeFiles/camera.dir/src/main.cpp.o: CMakeFiles/camera.dir/flags.make
CMakeFiles/camera.dir/src/main.cpp.o: /home/robert/VSG/shipProject/camera/src/main.cpp
CMakeFiles/camera.dir/src/main.cpp.o: CMakeFiles/camera.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/robert/VSG/shipProject/camera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/camera.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/camera.dir/src/main.cpp.o -MF CMakeFiles/camera.dir/src/main.cpp.o.d -o CMakeFiles/camera.dir/src/main.cpp.o -c /home/robert/VSG/shipProject/camera/src/main.cpp

CMakeFiles/camera.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/camera.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/VSG/shipProject/camera/src/main.cpp > CMakeFiles/camera.dir/src/main.cpp.i

CMakeFiles/camera.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/camera.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/VSG/shipProject/camera/src/main.cpp -o CMakeFiles/camera.dir/src/main.cpp.s

# Object files for target camera
camera_OBJECTS = \
"CMakeFiles/camera.dir/src/main.cpp.o"

# External object files for target camera
camera_EXTERNAL_OBJECTS =

camera: CMakeFiles/camera.dir/src/main.cpp.o
camera: CMakeFiles/camera.dir/build.make
camera: /usr/local/lib/libvsg.a
camera: /lib/libvsgXchange.a
camera: /usr/local/lib/libvsg.a
camera: /usr/lib/x86_64-linux-gnu/libvulkan.so
camera: /usr/lib/x86_64-linux-gnu/libglslang.a
camera: /usr/lib/x86_64-linux-gnu/libglslang-default-resource-limits.a
camera: /usr/lib/x86_64-linux-gnu/libSPIRV.a
camera: /usr/lib/x86_64-linux-gnu/libMachineIndependent.a
camera: /usr/lib/x86_64-linux-gnu/libOSDependent.a
camera: /usr/lib/x86_64-linux-gnu/libGenericCodeGen.a
camera: /usr/lib/x86_64-linux-gnu/libxcb.so
camera: /usr/lib/x86_64-linux-gnu/libfreetype.so
camera: /usr/lib/x86_64-linux-gnu/libassimp.so.5.2.0
camera: /usr/lib/x86_64-linux-gnu/libz.so
camera: /usr/lib/x86_64-linux-gnu/libdraco.so.4.0.0
camera: /usr/lib/x86_64-linux-gnu/librt.a
camera: /usr/lib/x86_64-linux-gnu/libcurl.so
camera: /usr/lib/x86_64-linux-gnu/libIlmImf-2_5.so.25.0.6
camera: /usr/lib/x86_64-linux-gnu/libImath-2_5.so.25.0.6
camera: /usr/lib/x86_64-linux-gnu/libHalf-2_5.so.25.0.6
camera: /usr/lib/x86_64-linux-gnu/libIexMath-2_5.so.25.0.6
camera: /usr/lib/x86_64-linux-gnu/libIlmThread-2_5.so.25.0.6
camera: /usr/lib/x86_64-linux-gnu/libIex-2_5.so.25.0.6
camera: /usr/lib/x86_64-linux-gnu/libz.so
camera: CMakeFiles/camera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/robert/VSG/shipProject/camera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable camera"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/camera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/camera.dir/build: camera
.PHONY : CMakeFiles/camera.dir/build

CMakeFiles/camera.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/camera.dir/cmake_clean.cmake
.PHONY : CMakeFiles/camera.dir/clean

CMakeFiles/camera.dir/depend:
	cd /home/robert/VSG/shipProject/camera/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robert/VSG/shipProject/camera /home/robert/VSG/shipProject/camera /home/robert/VSG/shipProject/camera/build /home/robert/VSG/shipProject/camera/build /home/robert/VSG/shipProject/camera/build/CMakeFiles/camera.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/camera.dir/depend

