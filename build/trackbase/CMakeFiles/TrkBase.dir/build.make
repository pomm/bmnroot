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
CMAKE_COMMAND = /opt/fairsoft/install/bin/cmake

# The command to remove a file.
RM = /opt/fairsoft/install/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /opt/fairsoft/install/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/merz/BMN/GIT/trunk_220814

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/merz/BMN/GIT/trunk_220814/build

# Include any dependencies generated for this target.
include trackbase/CMakeFiles/TrkBase.dir/depend.make

# Include the progress variables for this target.
include trackbase/CMakeFiles/TrkBase.dir/progress.make

# Include the compile flags for this target's objects.
include trackbase/CMakeFiles/TrkBase.dir/flags.make

trackbase/G__TrkBaseDict.cxx: ../trackbase/FairTrackPar.h
trackbase/G__TrkBaseDict.cxx: ../trackbase/FairTrackParP.h
trackbase/G__TrkBaseDict.cxx: ../trackbase/FairTrackParH.h
trackbase/G__TrkBaseDict.cxx: ../trackbase/FairGeaneUtil.h
trackbase/G__TrkBaseDict.cxx: ../trackbase/TrackBaseLinkDef.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/merz/BMN/GIT/trunk_220814/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating G__TrkBaseDict.cxx"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && LD_LIBRARY_PATH=/opt/fairsoft/install/lib/root: ROOTSYS=/opt/fairsoft/install /opt/fairsoft/install/bin/rootcint -f /home/merz/BMN/GIT/trunk_220814/build/trackbase/G__TrkBaseDict.cxx -c -p -I/opt/fairsoft/install/include/root -I/opt/fairsoft/install/include/Geant4 -I/home/merz/BMN/GIT/trunk_220814/fairtools -I/home/merz/BMN/GIT/trunk_220814/geobase -I/home/merz/BMN/GIT/trunk_220814/parbase -I/home/merz/BMN/GIT/trunk_220814/base -I/home/merz/BMN/GIT/trunk_220814/field -I/home/merz/BMN/GIT/trunk_220814/passive -I/home/merz/BMN/GIT/trunk_220814/genfit -I/home/merz/BMN/GIT/trunk_220814/trackbase FairTrackPar.h FairTrackParP.h FairTrackParH.h FairGeaneUtil.h TrackBaseLinkDef.h

trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o: trackbase/CMakeFiles/TrkBase.dir/flags.make
trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o: ../trackbase/FairTrackPar.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/merz/BMN/GIT/trunk_220814/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o -c /home/merz/BMN/GIT/trunk_220814/trackbase/FairTrackPar.cxx

trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrkBase.dir/FairTrackPar.cxx.i"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/merz/BMN/GIT/trunk_220814/trackbase/FairTrackPar.cxx > CMakeFiles/TrkBase.dir/FairTrackPar.cxx.i

trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrkBase.dir/FairTrackPar.cxx.s"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/merz/BMN/GIT/trunk_220814/trackbase/FairTrackPar.cxx -o CMakeFiles/TrkBase.dir/FairTrackPar.cxx.s

trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o.requires:
.PHONY : trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o.requires

trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o.provides: trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o.requires
	$(MAKE) -f trackbase/CMakeFiles/TrkBase.dir/build.make trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o.provides.build
.PHONY : trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o.provides

trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o.provides.build: trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o

trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o: trackbase/CMakeFiles/TrkBase.dir/flags.make
trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o: ../trackbase/FairTrackParP.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/merz/BMN/GIT/trunk_220814/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o -c /home/merz/BMN/GIT/trunk_220814/trackbase/FairTrackParP.cxx

trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrkBase.dir/FairTrackParP.cxx.i"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/merz/BMN/GIT/trunk_220814/trackbase/FairTrackParP.cxx > CMakeFiles/TrkBase.dir/FairTrackParP.cxx.i

trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrkBase.dir/FairTrackParP.cxx.s"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/merz/BMN/GIT/trunk_220814/trackbase/FairTrackParP.cxx -o CMakeFiles/TrkBase.dir/FairTrackParP.cxx.s

trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o.requires:
.PHONY : trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o.requires

trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o.provides: trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o.requires
	$(MAKE) -f trackbase/CMakeFiles/TrkBase.dir/build.make trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o.provides.build
.PHONY : trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o.provides

trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o.provides.build: trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o

trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o: trackbase/CMakeFiles/TrkBase.dir/flags.make
trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o: ../trackbase/FairTrackParH.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/merz/BMN/GIT/trunk_220814/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o -c /home/merz/BMN/GIT/trunk_220814/trackbase/FairTrackParH.cxx

trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrkBase.dir/FairTrackParH.cxx.i"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/merz/BMN/GIT/trunk_220814/trackbase/FairTrackParH.cxx > CMakeFiles/TrkBase.dir/FairTrackParH.cxx.i

trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrkBase.dir/FairTrackParH.cxx.s"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/merz/BMN/GIT/trunk_220814/trackbase/FairTrackParH.cxx -o CMakeFiles/TrkBase.dir/FairTrackParH.cxx.s

trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o.requires:
.PHONY : trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o.requires

trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o.provides: trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o.requires
	$(MAKE) -f trackbase/CMakeFiles/TrkBase.dir/build.make trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o.provides.build
.PHONY : trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o.provides

trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o.provides.build: trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o

trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o: trackbase/CMakeFiles/TrkBase.dir/flags.make
trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o: ../trackbase/FairGeaneUtil.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/merz/BMN/GIT/trunk_220814/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o -c /home/merz/BMN/GIT/trunk_220814/trackbase/FairGeaneUtil.cxx

trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.i"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/merz/BMN/GIT/trunk_220814/trackbase/FairGeaneUtil.cxx > CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.i

trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.s"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/merz/BMN/GIT/trunk_220814/trackbase/FairGeaneUtil.cxx -o CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.s

trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o.requires:
.PHONY : trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o.requires

trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o.provides: trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o.requires
	$(MAKE) -f trackbase/CMakeFiles/TrkBase.dir/build.make trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o.provides.build
.PHONY : trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o.provides

trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o.provides.build: trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o

trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o: trackbase/CMakeFiles/TrkBase.dir/flags.make
trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o: trackbase/G__TrkBaseDict.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/merz/BMN/GIT/trunk_220814/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o -c /home/merz/BMN/GIT/trunk_220814/build/trackbase/G__TrkBaseDict.cxx

trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.i"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/merz/BMN/GIT/trunk_220814/build/trackbase/G__TrkBaseDict.cxx > CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.i

trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.s"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/merz/BMN/GIT/trunk_220814/build/trackbase/G__TrkBaseDict.cxx -o CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.s

trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o.requires:
.PHONY : trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o.requires

trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o.provides: trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o.requires
	$(MAKE) -f trackbase/CMakeFiles/TrkBase.dir/build.make trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o.provides.build
.PHONY : trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o.provides

trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o.provides.build: trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o

# Object files for target TrkBase
TrkBase_OBJECTS = \
"CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o" \
"CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o" \
"CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o" \
"CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o" \
"CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o"

# External object files for target TrkBase
TrkBase_EXTERNAL_OBJECTS =

lib/libTrkBase.so.0.0.0: trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o
lib/libTrkBase.so.0.0.0: trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o
lib/libTrkBase.so.0.0.0: trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o
lib/libTrkBase.so.0.0.0: trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o
lib/libTrkBase.so.0.0.0: trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o
lib/libTrkBase.so.0.0.0: trackbase/CMakeFiles/TrkBase.dir/build.make
lib/libTrkBase.so.0.0.0: trackbase/CMakeFiles/TrkBase.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../lib/libTrkBase.so"
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TrkBase.dir/link.txt --verbose=$(VERBOSE)
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && $(CMAKE_COMMAND) -E cmake_symlink_library ../lib/libTrkBase.so.0.0.0 ../lib/libTrkBase.so.0 ../lib/libTrkBase.so

lib/libTrkBase.so.0: lib/libTrkBase.so.0.0.0

lib/libTrkBase.so: lib/libTrkBase.so.0.0.0

# Rule to build all files generated by this target.
trackbase/CMakeFiles/TrkBase.dir/build: lib/libTrkBase.so
.PHONY : trackbase/CMakeFiles/TrkBase.dir/build

trackbase/CMakeFiles/TrkBase.dir/requires: trackbase/CMakeFiles/TrkBase.dir/FairTrackPar.cxx.o.requires
trackbase/CMakeFiles/TrkBase.dir/requires: trackbase/CMakeFiles/TrkBase.dir/FairTrackParP.cxx.o.requires
trackbase/CMakeFiles/TrkBase.dir/requires: trackbase/CMakeFiles/TrkBase.dir/FairTrackParH.cxx.o.requires
trackbase/CMakeFiles/TrkBase.dir/requires: trackbase/CMakeFiles/TrkBase.dir/FairGeaneUtil.cxx.o.requires
trackbase/CMakeFiles/TrkBase.dir/requires: trackbase/CMakeFiles/TrkBase.dir/G__TrkBaseDict.cxx.o.requires
.PHONY : trackbase/CMakeFiles/TrkBase.dir/requires

trackbase/CMakeFiles/TrkBase.dir/clean:
	cd /home/merz/BMN/GIT/trunk_220814/build/trackbase && $(CMAKE_COMMAND) -P CMakeFiles/TrkBase.dir/cmake_clean.cmake
.PHONY : trackbase/CMakeFiles/TrkBase.dir/clean

trackbase/CMakeFiles/TrkBase.dir/depend: trackbase/G__TrkBaseDict.cxx
	cd /home/merz/BMN/GIT/trunk_220814/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/merz/BMN/GIT/trunk_220814 /home/merz/BMN/GIT/trunk_220814/trackbase /home/merz/BMN/GIT/trunk_220814/build /home/merz/BMN/GIT/trunk_220814/build/trackbase /home/merz/BMN/GIT/trunk_220814/build/trackbase/CMakeFiles/TrkBase.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : trackbase/CMakeFiles/TrkBase.dir/depend
