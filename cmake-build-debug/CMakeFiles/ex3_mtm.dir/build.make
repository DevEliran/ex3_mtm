# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Clion\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Clion\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\ex3_mtm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\ex3_mtm\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex3_mtm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex3_mtm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex3_mtm.dir/flags.make

CMakeFiles/ex3_mtm.dir/tests/UniqueArrayTest.cpp.obj: CMakeFiles/ex3_mtm.dir/flags.make
CMakeFiles/ex3_mtm.dir/tests/UniqueArrayTest.cpp.obj: CMakeFiles/ex3_mtm.dir/includes_CXX.rsp
CMakeFiles/ex3_mtm.dir/tests/UniqueArrayTest.cpp.obj: ../tests/UniqueArrayTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ex3_mtm\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex3_mtm.dir/tests/UniqueArrayTest.cpp.obj"
	D:\mingw(new)\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ex3_mtm.dir\tests\UniqueArrayTest.cpp.obj -c D:\ex3_mtm\tests\UniqueArrayTest.cpp

CMakeFiles/ex3_mtm.dir/tests/UniqueArrayTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex3_mtm.dir/tests/UniqueArrayTest.cpp.i"
	D:\mingw(new)\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ex3_mtm\tests\UniqueArrayTest.cpp > CMakeFiles\ex3_mtm.dir\tests\UniqueArrayTest.cpp.i

CMakeFiles/ex3_mtm.dir/tests/UniqueArrayTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex3_mtm.dir/tests/UniqueArrayTest.cpp.s"
	D:\mingw(new)\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ex3_mtm\tests\UniqueArrayTest.cpp -o CMakeFiles\ex3_mtm.dir\tests\UniqueArrayTest.cpp.s

# Object files for target ex3_mtm
ex3_mtm_OBJECTS = \
"CMakeFiles/ex3_mtm.dir/tests/UniqueArrayTest.cpp.obj"

# External object files for target ex3_mtm
ex3_mtm_EXTERNAL_OBJECTS =

ex3_mtm.exe: CMakeFiles/ex3_mtm.dir/tests/UniqueArrayTest.cpp.obj
ex3_mtm.exe: CMakeFiles/ex3_mtm.dir/build.make
ex3_mtm.exe: CMakeFiles/ex3_mtm.dir/linklibs.rsp
ex3_mtm.exe: CMakeFiles/ex3_mtm.dir/objects1.rsp
ex3_mtm.exe: CMakeFiles/ex3_mtm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\ex3_mtm\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ex3_mtm.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ex3_mtm.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex3_mtm.dir/build: ex3_mtm.exe

.PHONY : CMakeFiles/ex3_mtm.dir/build

CMakeFiles/ex3_mtm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ex3_mtm.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ex3_mtm.dir/clean

CMakeFiles/ex3_mtm.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\ex3_mtm D:\ex3_mtm D:\ex3_mtm\cmake-build-debug D:\ex3_mtm\cmake-build-debug D:\ex3_mtm\cmake-build-debug\CMakeFiles\ex3_mtm.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex3_mtm.dir/depend

