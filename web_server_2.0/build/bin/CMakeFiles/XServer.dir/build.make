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
CMAKE_SOURCE_DIR = /home/king/linux_service_code/web_server_2.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/king/linux_service_code/web_server_2.0/build

# Include any dependencies generated for this target.
include bin/CMakeFiles/XServer.dir/depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/XServer.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/XServer.dir/flags.make

bin/CMakeFiles/XServer.dir/config.cpp.o: bin/CMakeFiles/XServer.dir/flags.make
bin/CMakeFiles/XServer.dir/config.cpp.o: ../src/config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/king/linux_service_code/web_server_2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/CMakeFiles/XServer.dir/config.cpp.o"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XServer.dir/config.cpp.o -c /home/king/linux_service_code/web_server_2.0/src/config.cpp

bin/CMakeFiles/XServer.dir/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XServer.dir/config.cpp.i"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/king/linux_service_code/web_server_2.0/src/config.cpp > CMakeFiles/XServer.dir/config.cpp.i

bin/CMakeFiles/XServer.dir/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XServer.dir/config.cpp.s"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/king/linux_service_code/web_server_2.0/src/config.cpp -o CMakeFiles/XServer.dir/config.cpp.s

bin/CMakeFiles/XServer.dir/http.cpp.o: bin/CMakeFiles/XServer.dir/flags.make
bin/CMakeFiles/XServer.dir/http.cpp.o: ../src/http.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/king/linux_service_code/web_server_2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object bin/CMakeFiles/XServer.dir/http.cpp.o"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XServer.dir/http.cpp.o -c /home/king/linux_service_code/web_server_2.0/src/http.cpp

bin/CMakeFiles/XServer.dir/http.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XServer.dir/http.cpp.i"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/king/linux_service_code/web_server_2.0/src/http.cpp > CMakeFiles/XServer.dir/http.cpp.i

bin/CMakeFiles/XServer.dir/http.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XServer.dir/http.cpp.s"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/king/linux_service_code/web_server_2.0/src/http.cpp -o CMakeFiles/XServer.dir/http.cpp.s

bin/CMakeFiles/XServer.dir/log.cpp.o: bin/CMakeFiles/XServer.dir/flags.make
bin/CMakeFiles/XServer.dir/log.cpp.o: ../src/log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/king/linux_service_code/web_server_2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object bin/CMakeFiles/XServer.dir/log.cpp.o"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XServer.dir/log.cpp.o -c /home/king/linux_service_code/web_server_2.0/src/log.cpp

bin/CMakeFiles/XServer.dir/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XServer.dir/log.cpp.i"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/king/linux_service_code/web_server_2.0/src/log.cpp > CMakeFiles/XServer.dir/log.cpp.i

bin/CMakeFiles/XServer.dir/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XServer.dir/log.cpp.s"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/king/linux_service_code/web_server_2.0/src/log.cpp -o CMakeFiles/XServer.dir/log.cpp.s

bin/CMakeFiles/XServer.dir/main.cpp.o: bin/CMakeFiles/XServer.dir/flags.make
bin/CMakeFiles/XServer.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/king/linux_service_code/web_server_2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object bin/CMakeFiles/XServer.dir/main.cpp.o"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XServer.dir/main.cpp.o -c /home/king/linux_service_code/web_server_2.0/src/main.cpp

bin/CMakeFiles/XServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XServer.dir/main.cpp.i"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/king/linux_service_code/web_server_2.0/src/main.cpp > CMakeFiles/XServer.dir/main.cpp.i

bin/CMakeFiles/XServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XServer.dir/main.cpp.s"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/king/linux_service_code/web_server_2.0/src/main.cpp -o CMakeFiles/XServer.dir/main.cpp.s

bin/CMakeFiles/XServer.dir/server.cpp.o: bin/CMakeFiles/XServer.dir/flags.make
bin/CMakeFiles/XServer.dir/server.cpp.o: ../src/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/king/linux_service_code/web_server_2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object bin/CMakeFiles/XServer.dir/server.cpp.o"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XServer.dir/server.cpp.o -c /home/king/linux_service_code/web_server_2.0/src/server.cpp

bin/CMakeFiles/XServer.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XServer.dir/server.cpp.i"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/king/linux_service_code/web_server_2.0/src/server.cpp > CMakeFiles/XServer.dir/server.cpp.i

bin/CMakeFiles/XServer.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XServer.dir/server.cpp.s"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/king/linux_service_code/web_server_2.0/src/server.cpp -o CMakeFiles/XServer.dir/server.cpp.s

bin/CMakeFiles/XServer.dir/sqlconn_pool.cpp.o: bin/CMakeFiles/XServer.dir/flags.make
bin/CMakeFiles/XServer.dir/sqlconn_pool.cpp.o: ../src/sqlconn_pool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/king/linux_service_code/web_server_2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object bin/CMakeFiles/XServer.dir/sqlconn_pool.cpp.o"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XServer.dir/sqlconn_pool.cpp.o -c /home/king/linux_service_code/web_server_2.0/src/sqlconn_pool.cpp

bin/CMakeFiles/XServer.dir/sqlconn_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XServer.dir/sqlconn_pool.cpp.i"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/king/linux_service_code/web_server_2.0/src/sqlconn_pool.cpp > CMakeFiles/XServer.dir/sqlconn_pool.cpp.i

bin/CMakeFiles/XServer.dir/sqlconn_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XServer.dir/sqlconn_pool.cpp.s"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/king/linux_service_code/web_server_2.0/src/sqlconn_pool.cpp -o CMakeFiles/XServer.dir/sqlconn_pool.cpp.s

bin/CMakeFiles/XServer.dir/timer.cpp.o: bin/CMakeFiles/XServer.dir/flags.make
bin/CMakeFiles/XServer.dir/timer.cpp.o: ../src/timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/king/linux_service_code/web_server_2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object bin/CMakeFiles/XServer.dir/timer.cpp.o"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XServer.dir/timer.cpp.o -c /home/king/linux_service_code/web_server_2.0/src/timer.cpp

bin/CMakeFiles/XServer.dir/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XServer.dir/timer.cpp.i"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/king/linux_service_code/web_server_2.0/src/timer.cpp > CMakeFiles/XServer.dir/timer.cpp.i

bin/CMakeFiles/XServer.dir/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XServer.dir/timer.cpp.s"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/king/linux_service_code/web_server_2.0/src/timer.cpp -o CMakeFiles/XServer.dir/timer.cpp.s

# Object files for target XServer
XServer_OBJECTS = \
"CMakeFiles/XServer.dir/config.cpp.o" \
"CMakeFiles/XServer.dir/http.cpp.o" \
"CMakeFiles/XServer.dir/log.cpp.o" \
"CMakeFiles/XServer.dir/main.cpp.o" \
"CMakeFiles/XServer.dir/server.cpp.o" \
"CMakeFiles/XServer.dir/sqlconn_pool.cpp.o" \
"CMakeFiles/XServer.dir/timer.cpp.o"

# External object files for target XServer
XServer_EXTERNAL_OBJECTS =

bin/XServer: bin/CMakeFiles/XServer.dir/config.cpp.o
bin/XServer: bin/CMakeFiles/XServer.dir/http.cpp.o
bin/XServer: bin/CMakeFiles/XServer.dir/log.cpp.o
bin/XServer: bin/CMakeFiles/XServer.dir/main.cpp.o
bin/XServer: bin/CMakeFiles/XServer.dir/server.cpp.o
bin/XServer: bin/CMakeFiles/XServer.dir/sqlconn_pool.cpp.o
bin/XServer: bin/CMakeFiles/XServer.dir/timer.cpp.o
bin/XServer: bin/CMakeFiles/XServer.dir/build.make
bin/XServer: /usr/lib/x86_64-linux-gnu/libmysqlclient.so
bin/XServer: bin/CMakeFiles/XServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/king/linux_service_code/web_server_2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable XServer"
	cd /home/king/linux_service_code/web_server_2.0/build/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/XServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/XServer.dir/build: bin/XServer

.PHONY : bin/CMakeFiles/XServer.dir/build

bin/CMakeFiles/XServer.dir/clean:
	cd /home/king/linux_service_code/web_server_2.0/build/bin && $(CMAKE_COMMAND) -P CMakeFiles/XServer.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/XServer.dir/clean

bin/CMakeFiles/XServer.dir/depend:
	cd /home/king/linux_service_code/web_server_2.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/king/linux_service_code/web_server_2.0 /home/king/linux_service_code/web_server_2.0/src /home/king/linux_service_code/web_server_2.0/build /home/king/linux_service_code/web_server_2.0/build/bin /home/king/linux_service_code/web_server_2.0/build/bin/CMakeFiles/XServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/XServer.dir/depend

