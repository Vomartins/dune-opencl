# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl/build-cmake

# Utility rule file for install_python.

# Include any custom commands dependencies for this target.
include CMakeFiles/install_python.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/install_python.dir/progress.make

install_python: CMakeFiles/install_python.dir/build.make
.PHONY : install_python

# Rule to build all files generated by this target.
CMakeFiles/install_python.dir/build: install_python
.PHONY : CMakeFiles/install_python.dir/build

CMakeFiles/install_python.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/install_python.dir/cmake_clean.cmake
.PHONY : CMakeFiles/install_python.dir/clean

CMakeFiles/install_python.dir/depend:
	cd /home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl/build-cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl /home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl /home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl/build-cmake /home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl/build-cmake /home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl/build-cmake/CMakeFiles/install_python.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/install_python.dir/depend

