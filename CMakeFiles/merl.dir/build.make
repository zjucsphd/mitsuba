# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pony/mitsuba

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pony/mitsuba

# Include any dependencies generated for this target.
include CMakeFiles/merl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/merl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/merl.dir/flags.make

CMakeFiles/merl.dir/MERL.cpp.o: CMakeFiles/merl.dir/flags.make
CMakeFiles/merl.dir/MERL.cpp.o: MERL.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pony/mitsuba/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/merl.dir/MERL.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/merl.dir/MERL.cpp.o -c /home/pony/mitsuba/MERL.cpp

CMakeFiles/merl.dir/MERL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/merl.dir/MERL.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pony/mitsuba/MERL.cpp > CMakeFiles/merl.dir/MERL.cpp.i

CMakeFiles/merl.dir/MERL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/merl.dir/MERL.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pony/mitsuba/MERL.cpp -o CMakeFiles/merl.dir/MERL.cpp.s

CMakeFiles/merl.dir/MERL.cpp.o.requires:
.PHONY : CMakeFiles/merl.dir/MERL.cpp.o.requires

CMakeFiles/merl.dir/MERL.cpp.o.provides: CMakeFiles/merl.dir/MERL.cpp.o.requires
	$(MAKE) -f CMakeFiles/merl.dir/build.make CMakeFiles/merl.dir/MERL.cpp.o.provides.build
.PHONY : CMakeFiles/merl.dir/MERL.cpp.o.provides

CMakeFiles/merl.dir/MERL.cpp.o.provides.build: CMakeFiles/merl.dir/MERL.cpp.o

# Object files for target merl
merl_OBJECTS = \
"CMakeFiles/merl.dir/MERL.cpp.o"

# External object files for target merl
merl_EXTERNAL_OBJECTS =

binaries/plugins/merl.so: CMakeFiles/merl.dir/MERL.cpp.o
binaries/plugins/merl.so: CMakeFiles/merl.dir/build.make
binaries/plugins/merl.so: binaries/libmitsuba-core.so
binaries/plugins/merl.so: binaries/libmitsuba-render.so
binaries/plugins/merl.so: binaries/libmitsuba-hw.so
binaries/plugins/merl.so: binaries/libmitsuba-render.so
binaries/plugins/merl.so: binaries/libmitsuba-core.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libz.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libpng.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libz.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libpng.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libjpeg.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libHalf.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libIex.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libImath.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libIlmThread.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libIlmImf.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libpthread.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libIlmImf.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libpthread.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libfftw3.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libfftw3_threads.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libxerces-c.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libGLU.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libGL.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libSM.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libICE.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libX11.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libXext.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libGLEWmx.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libGLU.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libGL.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libSM.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libICE.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libX11.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libXext.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libGLEWmx.so
binaries/plugins/merl.so: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
binaries/plugins/merl.so: CMakeFiles/merl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared module binaries/plugins/merl.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/merl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/merl.dir/build: binaries/plugins/merl.so
.PHONY : CMakeFiles/merl.dir/build

CMakeFiles/merl.dir/requires: CMakeFiles/merl.dir/MERL.cpp.o.requires
.PHONY : CMakeFiles/merl.dir/requires

CMakeFiles/merl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/merl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/merl.dir/clean

CMakeFiles/merl.dir/depend:
	cd /home/pony/mitsuba && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pony/mitsuba /home/pony/mitsuba /home/pony/mitsuba /home/pony/mitsuba /home/pony/mitsuba/CMakeFiles/merl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/merl.dir/depend

