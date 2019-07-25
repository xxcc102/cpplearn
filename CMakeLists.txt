#root
cmake_minimum_required(VERSION 3.5)

project(Algorithm_TEST)

set(CMAKE_VERBOSE_MAKEFILE on)

add_definitions(-DUNICODE -D_UNICODE)
set(CMAKE_BUILD_TYPE Debug)


if (WIN32 AND NOT MINGW)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/win)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/win)   		
elseif (UNIX AND NOT ANDROID)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -fvisibility=hidden -fPIC") 
    
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O1")
    
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/linux)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/linux)
endif()

add_subdirectory(src)
#add_subdirectory(include)
