# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/soroush/Desktop/work/hiredis/source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/soroush/Desktop/work/hiredis

# Include any dependencies generated for this target.
include CMakeFiles/lib_redis.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lib_redis.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lib_redis.dir/flags.make

CMakeFiles/lib_redis.dir/Main.cpp.o: CMakeFiles/lib_redis.dir/flags.make
CMakeFiles/lib_redis.dir/Main.cpp.o: source/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/soroush/Desktop/work/hiredis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lib_redis.dir/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lib_redis.dir/Main.cpp.o -c /home/soroush/Desktop/work/hiredis/source/Main.cpp

CMakeFiles/lib_redis.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_redis.dir/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/soroush/Desktop/work/hiredis/source/Main.cpp > CMakeFiles/lib_redis.dir/Main.cpp.i

CMakeFiles/lib_redis.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_redis.dir/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/soroush/Desktop/work/hiredis/source/Main.cpp -o CMakeFiles/lib_redis.dir/Main.cpp.s

# Object files for target lib_redis
lib_redis_OBJECTS = \
"CMakeFiles/lib_redis.dir/Main.cpp.o"

# External object files for target lib_redis
lib_redis_EXTERNAL_OBJECTS =

lib_redis: CMakeFiles/lib_redis.dir/Main.cpp.o
lib_redis: CMakeFiles/lib_redis.dir/build.make
lib_redis: libsomredis.a
lib_redis: CMakeFiles/lib_redis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/soroush/Desktop/work/hiredis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lib_redis"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib_redis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lib_redis.dir/build: lib_redis

.PHONY : CMakeFiles/lib_redis.dir/build

CMakeFiles/lib_redis.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lib_redis.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lib_redis.dir/clean

CMakeFiles/lib_redis.dir/depend:
	cd /home/soroush/Desktop/work/hiredis && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/soroush/Desktop/work/hiredis/source /home/soroush/Desktop/work/hiredis/source /home/soroush/Desktop/work/hiredis /home/soroush/Desktop/work/hiredis /home/soroush/Desktop/work/hiredis/CMakeFiles/lib_redis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lib_redis.dir/depend
