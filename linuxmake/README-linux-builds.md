BCT.Workflow.Aggregates.CPP build on Fedora readme

This readme contains two sections based upon how the source is obtained: from "Git clone" vs "NuGet install".
The build process is orchestrated by a makefile calling cmake utility to build the 3 Workflow aggregates-cpp
projects: CPPLib, CPP.GeneratedCode, and CPP.Test.

==================================================================================
SECTION 1: repo cloned from Git

To build on Fedora 31 from terminal shell... the output goes to "build" subfolder

1. do a git clone to Fedora

2. navigate to bct-worfklow-aggregates-cpp\src subfolder

3. to build Workflow.Aggregates in Release mode and run the unit tests
	> make all run-tests

4. navigate to folder build/Release to find .so files, unit test executables, along with the temporary cmake artifacts
	> ls -la build/Release

5. to build Workflow.Aggregates in Debug mode and run the unit tests
	> make all run-tests BUILD_TYPE=Debug

6. to clean up the build subfolder
	> make clean

7. to build within a Docker container
	> ./dockerBuild.sh rpnbuilder make all run-tests 
	
	> ./dockerBuild.sh rpnbuilder make all run-tests BUILD_TYPE=Debug


==================================================================================
SECTION 2: source files from "NuGet install"

The source code folders and contents are very different than cloning from Git.
The linuxmake subfolder contains all that is needed for building BCT.Workflow.Aggregates.CPP, which are:
   
   - CMakeList.txt				- CMake file specific to RPN library
   - getNugetSourceFiles.sh		- bash script file for collecting the source files
 


 