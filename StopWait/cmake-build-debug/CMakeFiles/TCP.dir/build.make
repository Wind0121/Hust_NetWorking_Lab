# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /home/kezzy/.cache/JetBrains/RemoteDev/dist/7d288fc846b32_CLion-233.8264.3/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/kezzy/.cache/JetBrains/RemoteDev/dist/7d288fc846b32_CLion-233.8264.3/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TCP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TCP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TCP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TCP.dir/flags.make

CMakeFiles/TCP.dir/src/TCP.cpp.o: CMakeFiles/TCP.dir/flags.make
CMakeFiles/TCP.dir/src/TCP.cpp.o: /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCP.cpp
CMakeFiles/TCP.dir/src/TCP.cpp.o: CMakeFiles/TCP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TCP.dir/src/TCP.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TCP.dir/src/TCP.cpp.o -MF CMakeFiles/TCP.dir/src/TCP.cpp.o.d -o CMakeFiles/TCP.dir/src/TCP.cpp.o -c /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCP.cpp

CMakeFiles/TCP.dir/src/TCP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TCP.dir/src/TCP.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCP.cpp > CMakeFiles/TCP.dir/src/TCP.cpp.i

CMakeFiles/TCP.dir/src/TCP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TCP.dir/src/TCP.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCP.cpp -o CMakeFiles/TCP.dir/src/TCP.cpp.s

CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.o: CMakeFiles/TCP.dir/flags.make
CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.o: /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCPRdtReceiver.cpp
CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.o: CMakeFiles/TCP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.o -MF CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.o.d -o CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.o -c /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCPRdtReceiver.cpp

CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCPRdtReceiver.cpp > CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.i

CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCPRdtReceiver.cpp -o CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.s

CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.o: CMakeFiles/TCP.dir/flags.make
CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.o: /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCPRdtSender.cpp
CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.o: CMakeFiles/TCP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.o -MF CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.o.d -o CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.o -c /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCPRdtSender.cpp

CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCPRdtSender.cpp > CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.i

CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/src/TCPRdtSender.cpp -o CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.s

# Object files for target TCP
TCP_OBJECTS = \
"CMakeFiles/TCP.dir/src/TCP.cpp.o" \
"CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.o" \
"CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.o"

# External object files for target TCP
TCP_EXTERNAL_OBJECTS =

/mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/bin/TCP: CMakeFiles/TCP.dir/src/TCP.cpp.o
/mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/bin/TCP: CMakeFiles/TCP.dir/src/TCPRdtReceiver.cpp.o
/mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/bin/TCP: CMakeFiles/TCP.dir/src/TCPRdtSender.cpp.o
/mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/bin/TCP: CMakeFiles/TCP.dir/build.make
/mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/bin/TCP: /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/lib/libnetsim.a
/mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/bin/TCP: CMakeFiles/TCP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/bin/TCP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TCP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TCP.dir/build: /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/bin/TCP
.PHONY : CMakeFiles/TCP.dir/build

CMakeFiles/TCP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TCP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TCP.dir/clean

CMakeFiles/TCP.dir/depend:
	cd /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/cmake-build-debug /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/cmake-build-debug /mnt/e/Clion_Project/Net_Lab_2_TCP/StopWait/cmake-build-debug/CMakeFiles/TCP.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/TCP.dir/depend
