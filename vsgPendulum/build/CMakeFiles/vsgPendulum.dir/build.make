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
CMAKE_COMMAND = /snap/cmake/1413/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1413/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/robert/VSG/vsgPendulum

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robert/VSG/vsgPendulum/build

# Include any dependencies generated for this target.
include CMakeFiles/vsgPendulum.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/vsgPendulum.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/vsgPendulum.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vsgPendulum.dir/flags.make

CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.o: CMakeFiles/vsgPendulum.dir/flags.make
CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.o: /home/robert/VSG/vsgPendulum/src/builderModels.cpp
CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.o: CMakeFiles/vsgPendulum.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/robert/VSG/vsgPendulum/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.o -MF CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.o.d -o CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.o -c /home/robert/VSG/vsgPendulum/src/builderModels.cpp

CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/VSG/vsgPendulum/src/builderModels.cpp > CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.i

CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/VSG/vsgPendulum/src/builderModels.cpp -o CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.s

CMakeFiles/vsgPendulum.dir/src/main.cpp.o: CMakeFiles/vsgPendulum.dir/flags.make
CMakeFiles/vsgPendulum.dir/src/main.cpp.o: /home/robert/VSG/vsgPendulum/src/main.cpp
CMakeFiles/vsgPendulum.dir/src/main.cpp.o: CMakeFiles/vsgPendulum.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/robert/VSG/vsgPendulum/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/vsgPendulum.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vsgPendulum.dir/src/main.cpp.o -MF CMakeFiles/vsgPendulum.dir/src/main.cpp.o.d -o CMakeFiles/vsgPendulum.dir/src/main.cpp.o -c /home/robert/VSG/vsgPendulum/src/main.cpp

CMakeFiles/vsgPendulum.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vsgPendulum.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/VSG/vsgPendulum/src/main.cpp > CMakeFiles/vsgPendulum.dir/src/main.cpp.i

CMakeFiles/vsgPendulum.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vsgPendulum.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/VSG/vsgPendulum/src/main.cpp -o CMakeFiles/vsgPendulum.dir/src/main.cpp.s

CMakeFiles/vsgPendulum.dir/src/pMath.cpp.o: CMakeFiles/vsgPendulum.dir/flags.make
CMakeFiles/vsgPendulum.dir/src/pMath.cpp.o: /home/robert/VSG/vsgPendulum/src/pMath.cpp
CMakeFiles/vsgPendulum.dir/src/pMath.cpp.o: CMakeFiles/vsgPendulum.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/robert/VSG/vsgPendulum/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/vsgPendulum.dir/src/pMath.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vsgPendulum.dir/src/pMath.cpp.o -MF CMakeFiles/vsgPendulum.dir/src/pMath.cpp.o.d -o CMakeFiles/vsgPendulum.dir/src/pMath.cpp.o -c /home/robert/VSG/vsgPendulum/src/pMath.cpp

CMakeFiles/vsgPendulum.dir/src/pMath.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vsgPendulum.dir/src/pMath.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/VSG/vsgPendulum/src/pMath.cpp > CMakeFiles/vsgPendulum.dir/src/pMath.cpp.i

CMakeFiles/vsgPendulum.dir/src/pMath.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vsgPendulum.dir/src/pMath.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/VSG/vsgPendulum/src/pMath.cpp -o CMakeFiles/vsgPendulum.dir/src/pMath.cpp.s

# Object files for target vsgPendulum
vsgPendulum_OBJECTS = \
"CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.o" \
"CMakeFiles/vsgPendulum.dir/src/main.cpp.o" \
"CMakeFiles/vsgPendulum.dir/src/pMath.cpp.o"

# External object files for target vsgPendulum
vsgPendulum_EXTERNAL_OBJECTS =

vsgPendulum: CMakeFiles/vsgPendulum.dir/src/builderModels.cpp.o
vsgPendulum: CMakeFiles/vsgPendulum.dir/src/main.cpp.o
vsgPendulum: CMakeFiles/vsgPendulum.dir/src/pMath.cpp.o
vsgPendulum: CMakeFiles/vsgPendulum.dir/build.make
vsgPendulum: /usr/local/lib/libvsg.a
vsgPendulum: /lib/libvsgXchange.a
vsgPendulum: /usr/local/lib/libvsg.a
vsgPendulum: /usr/lib/x86_64-linux-gnu/libvulkan.so
vsgPendulum: /usr/lib/x86_64-linux-gnu/libglslang.a
vsgPendulum: /usr/lib/x86_64-linux-gnu/libglslang-default-resource-limits.a
vsgPendulum: /usr/lib/x86_64-linux-gnu/libSPIRV.a
vsgPendulum: /usr/lib/x86_64-linux-gnu/libMachineIndependent.a
vsgPendulum: /usr/lib/x86_64-linux-gnu/libOSDependent.a
vsgPendulum: /usr/lib/x86_64-linux-gnu/libGenericCodeGen.a
vsgPendulum: /usr/lib/x86_64-linux-gnu/libxcb.so
vsgPendulum: /usr/lib/x86_64-linux-gnu/libfreetype.so
vsgPendulum: /usr/lib/x86_64-linux-gnu/libassimp.so.5.2.0
vsgPendulum: /usr/lib/x86_64-linux-gnu/libz.so
vsgPendulum: /usr/lib/x86_64-linux-gnu/libdraco.so.4.0.0
vsgPendulum: /usr/lib/x86_64-linux-gnu/librt.a
vsgPendulum: /usr/lib/x86_64-linux-gnu/libcurl.so
vsgPendulum: /usr/lib/x86_64-linux-gnu/libIlmImf-2_5.so.25.0.6
vsgPendulum: /usr/lib/x86_64-linux-gnu/libImath-2_5.so.25.0.6
vsgPendulum: /usr/lib/x86_64-linux-gnu/libHalf-2_5.so.25.0.6
vsgPendulum: /usr/lib/x86_64-linux-gnu/libIexMath-2_5.so.25.0.6
vsgPendulum: /usr/lib/x86_64-linux-gnu/libIlmThread-2_5.so.25.0.6
vsgPendulum: /usr/lib/x86_64-linux-gnu/libIex-2_5.so.25.0.6
vsgPendulum: /usr/lib/x86_64-linux-gnu/libz.so
vsgPendulum: CMakeFiles/vsgPendulum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/robert/VSG/vsgPendulum/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable vsgPendulum"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vsgPendulum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vsgPendulum.dir/build: vsgPendulum
.PHONY : CMakeFiles/vsgPendulum.dir/build

CMakeFiles/vsgPendulum.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vsgPendulum.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vsgPendulum.dir/clean

CMakeFiles/vsgPendulum.dir/depend:
	cd /home/robert/VSG/vsgPendulum/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robert/VSG/vsgPendulum /home/robert/VSG/vsgPendulum /home/robert/VSG/vsgPendulum/build /home/robert/VSG/vsgPendulum/build /home/robert/VSG/vsgPendulum/build/CMakeFiles/vsgPendulum.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/vsgPendulum.dir/depend

