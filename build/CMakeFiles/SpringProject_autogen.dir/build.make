# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/petersampson/SpringProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/petersampson/SpringProject/build

# Utility rule file for SpringProject_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/SpringProject_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SpringProject_autogen.dir/progress.make

CMakeFiles/SpringProject_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/petersampson/SpringProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target SpringProject"
	/Applications/CMake.app/Contents/bin/cmake -E cmake_autogen /Users/petersampson/SpringProject/build/CMakeFiles/SpringProject_autogen.dir/AutogenInfo.json Debug

SpringProject_autogen: CMakeFiles/SpringProject_autogen
SpringProject_autogen: CMakeFiles/SpringProject_autogen.dir/build.make
.PHONY : SpringProject_autogen

# Rule to build all files generated by this target.
CMakeFiles/SpringProject_autogen.dir/build: SpringProject_autogen
.PHONY : CMakeFiles/SpringProject_autogen.dir/build

CMakeFiles/SpringProject_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SpringProject_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SpringProject_autogen.dir/clean

CMakeFiles/SpringProject_autogen.dir/depend:
	cd /Users/petersampson/SpringProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/petersampson/SpringProject /Users/petersampson/SpringProject /Users/petersampson/SpringProject/build /Users/petersampson/SpringProject/build /Users/petersampson/SpringProject/build/CMakeFiles/SpringProject_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SpringProject_autogen.dir/depend

