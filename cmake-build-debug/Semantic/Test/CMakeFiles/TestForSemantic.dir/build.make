# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/atri/CLionProjects/Compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/atri/CLionProjects/Compiler/cmake-build-debug

# Include any dependencies generated for this target.
include Semantic/Test/CMakeFiles/TestForSemantic.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Semantic/Test/CMakeFiles/TestForSemantic.dir/compiler_depend.make

# Include the progress variables for this target.
include Semantic/Test/CMakeFiles/TestForSemantic.dir/progress.make

# Include the compile flags for this target's objects.
include Semantic/Test/CMakeFiles/TestForSemantic.dir/flags.make

Semantic/Test/CMakeFiles/TestForSemantic.dir/a.cpp.o: Semantic/Test/CMakeFiles/TestForSemantic.dir/flags.make
Semantic/Test/CMakeFiles/TestForSemantic.dir/a.cpp.o: /Users/atri/CLionProjects/Compiler/Semantic/Test/a.cpp
Semantic/Test/CMakeFiles/TestForSemantic.dir/a.cpp.o: Semantic/Test/CMakeFiles/TestForSemantic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/atri/CLionProjects/Compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Semantic/Test/CMakeFiles/TestForSemantic.dir/a.cpp.o"
	cd /Users/atri/CLionProjects/Compiler/cmake-build-debug/Semantic/Test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Semantic/Test/CMakeFiles/TestForSemantic.dir/a.cpp.o -MF CMakeFiles/TestForSemantic.dir/a.cpp.o.d -o CMakeFiles/TestForSemantic.dir/a.cpp.o -c /Users/atri/CLionProjects/Compiler/Semantic/Test/a.cpp

Semantic/Test/CMakeFiles/TestForSemantic.dir/a.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TestForSemantic.dir/a.cpp.i"
	cd /Users/atri/CLionProjects/Compiler/cmake-build-debug/Semantic/Test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/atri/CLionProjects/Compiler/Semantic/Test/a.cpp > CMakeFiles/TestForSemantic.dir/a.cpp.i

Semantic/Test/CMakeFiles/TestForSemantic.dir/a.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TestForSemantic.dir/a.cpp.s"
	cd /Users/atri/CLionProjects/Compiler/cmake-build-debug/Semantic/Test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/atri/CLionProjects/Compiler/Semantic/Test/a.cpp -o CMakeFiles/TestForSemantic.dir/a.cpp.s

# Object files for target TestForSemantic
TestForSemantic_OBJECTS = \
"CMakeFiles/TestForSemantic.dir/a.cpp.o"

# External object files for target TestForSemantic
TestForSemantic_EXTERNAL_OBJECTS =

Semantic/Test/TestForSemantic: Semantic/Test/CMakeFiles/TestForSemantic.dir/a.cpp.o
Semantic/Test/TestForSemantic: Semantic/Test/CMakeFiles/TestForSemantic.dir/build.make
Semantic/Test/TestForSemantic: lib/libgtest.a
Semantic/Test/TestForSemantic: lib/libgtest_main.a
Semantic/Test/TestForSemantic: lib/libgtest.a
Semantic/Test/TestForSemantic: Semantic/Test/CMakeFiles/TestForSemantic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/atri/CLionProjects/Compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TestForSemantic"
	cd /Users/atri/CLionProjects/Compiler/cmake-build-debug/Semantic/Test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestForSemantic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Semantic/Test/CMakeFiles/TestForSemantic.dir/build: Semantic/Test/TestForSemantic
.PHONY : Semantic/Test/CMakeFiles/TestForSemantic.dir/build

Semantic/Test/CMakeFiles/TestForSemantic.dir/clean:
	cd /Users/atri/CLionProjects/Compiler/cmake-build-debug/Semantic/Test && $(CMAKE_COMMAND) -P CMakeFiles/TestForSemantic.dir/cmake_clean.cmake
.PHONY : Semantic/Test/CMakeFiles/TestForSemantic.dir/clean

Semantic/Test/CMakeFiles/TestForSemantic.dir/depend:
	cd /Users/atri/CLionProjects/Compiler/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/atri/CLionProjects/Compiler /Users/atri/CLionProjects/Compiler/Semantic/Test /Users/atri/CLionProjects/Compiler/cmake-build-debug /Users/atri/CLionProjects/Compiler/cmake-build-debug/Semantic/Test /Users/atri/CLionProjects/Compiler/cmake-build-debug/Semantic/Test/CMakeFiles/TestForSemantic.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Semantic/Test/CMakeFiles/TestForSemantic.dir/depend

