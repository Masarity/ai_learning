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
CMAKE_SOURCE_DIR = /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build

# Include any dependencies generated for this target.
include CMakeFiles/run.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/run.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/run.dir/flags.make

CMakeFiles/run.dir/src/main2.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/main2.cpp.o: ../src/main2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/run.dir/src/main2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/src/main2.cpp.o -c /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/main2.cpp

CMakeFiles/run.dir/src/main2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/main2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/main2.cpp > CMakeFiles/run.dir/src/main2.cpp.i

CMakeFiles/run.dir/src/main2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/main2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/main2.cpp -o CMakeFiles/run.dir/src/main2.cpp.s

CMakeFiles/run.dir/src/Card.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/Card.cpp.o: ../src/Card.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/run.dir/src/Card.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/src/Card.cpp.o -c /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Card.cpp

CMakeFiles/run.dir/src/Card.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/Card.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Card.cpp > CMakeFiles/run.dir/src/Card.cpp.i

CMakeFiles/run.dir/src/Card.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/Card.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Card.cpp -o CMakeFiles/run.dir/src/Card.cpp.s

CMakeFiles/run.dir/src/Agent.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/Agent.cpp.o: ../src/Agent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/run.dir/src/Agent.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/src/Agent.cpp.o -c /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Agent.cpp

CMakeFiles/run.dir/src/Agent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/Agent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Agent.cpp > CMakeFiles/run.dir/src/Agent.cpp.i

CMakeFiles/run.dir/src/Agent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/Agent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Agent.cpp -o CMakeFiles/run.dir/src/Agent.cpp.s

CMakeFiles/run.dir/src/Player.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/Player.cpp.o: ../src/Player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/run.dir/src/Player.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/src/Player.cpp.o -c /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Player.cpp

CMakeFiles/run.dir/src/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/Player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Player.cpp > CMakeFiles/run.dir/src/Player.cpp.i

CMakeFiles/run.dir/src/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/Player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Player.cpp -o CMakeFiles/run.dir/src/Player.cpp.s

CMakeFiles/run.dir/src/Dealer.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/Dealer.cpp.o: ../src/Dealer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/run.dir/src/Dealer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/src/Dealer.cpp.o -c /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Dealer.cpp

CMakeFiles/run.dir/src/Dealer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/Dealer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Dealer.cpp > CMakeFiles/run.dir/src/Dealer.cpp.i

CMakeFiles/run.dir/src/Dealer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/Dealer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Dealer.cpp -o CMakeFiles/run.dir/src/Dealer.cpp.s

CMakeFiles/run.dir/src/Environment.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/Environment.cpp.o: ../src/Environment.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/run.dir/src/Environment.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/src/Environment.cpp.o -c /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Environment.cpp

CMakeFiles/run.dir/src/Environment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/Environment.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Environment.cpp > CMakeFiles/run.dir/src/Environment.cpp.i

CMakeFiles/run.dir/src/Environment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/Environment.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/Environment.cpp -o CMakeFiles/run.dir/src/Environment.cpp.s

CMakeFiles/run.dir/src/SimpleGnuplot.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/SimpleGnuplot.cpp.o: ../src/SimpleGnuplot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/run.dir/src/SimpleGnuplot.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/src/SimpleGnuplot.cpp.o -c /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/SimpleGnuplot.cpp

CMakeFiles/run.dir/src/SimpleGnuplot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/SimpleGnuplot.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/SimpleGnuplot.cpp > CMakeFiles/run.dir/src/SimpleGnuplot.cpp.i

CMakeFiles/run.dir/src/SimpleGnuplot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/SimpleGnuplot.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/src/SimpleGnuplot.cpp -o CMakeFiles/run.dir/src/SimpleGnuplot.cpp.s

# Object files for target run
run_OBJECTS = \
"CMakeFiles/run.dir/src/main2.cpp.o" \
"CMakeFiles/run.dir/src/Card.cpp.o" \
"CMakeFiles/run.dir/src/Agent.cpp.o" \
"CMakeFiles/run.dir/src/Player.cpp.o" \
"CMakeFiles/run.dir/src/Dealer.cpp.o" \
"CMakeFiles/run.dir/src/Environment.cpp.o" \
"CMakeFiles/run.dir/src/SimpleGnuplot.cpp.o"

# External object files for target run
run_EXTERNAL_OBJECTS =

run: CMakeFiles/run.dir/src/main2.cpp.o
run: CMakeFiles/run.dir/src/Card.cpp.o
run: CMakeFiles/run.dir/src/Agent.cpp.o
run: CMakeFiles/run.dir/src/Player.cpp.o
run: CMakeFiles/run.dir/src/Dealer.cpp.o
run: CMakeFiles/run.dir/src/Environment.cpp.o
run: CMakeFiles/run.dir/src/SimpleGnuplot.cpp.o
run: CMakeFiles/run.dir/build.make
run: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so.1.71.0
run: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
run: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
run: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
run: CMakeFiles/run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable run"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/run.dir/build: run

.PHONY : CMakeFiles/run.dir/build

CMakeFiles/run.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/run.dir/cmake_clean.cmake
.PHONY : CMakeFiles/run.dir/clean

CMakeFiles/run.dir/depend:
	cd /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build /home/masa/learning/ai_learning/rl_learning/cpp_rl/blackjack/build/CMakeFiles/run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/run.dir/depend
