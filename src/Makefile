#! /bin/bash

BUILD_TYPE := Release


.PHONY: all clean run-tests
# comment out the cmake 3.16.3 command because -B is not supported in 3.11
# instead manually generate cmake dependencies in the build folder
#cmake -S . -B ./build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE:STRING=Debug


all:
	mkdir -p build/${BUILD_TYPE} && \
	pushd build/${BUILD_TYPE} && \
	cmake -S ../../. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE:STRING=${BUILD_TYPE} && \
	popd && \
	cmake --build ./build/${BUILD_TYPE} --target all



######################
# clean up and prepare
######################
clean:
	rm -rf build

run-tests: all
	pushd build/${BUILD_TYPE} && \
	ctest --verbose && \
	popd


