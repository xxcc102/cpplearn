#设置gtest的测试配置

#设置生成的lib库和头文件
set(Test_INCLUDE_DIR 
	${LIBRARY_OUTPUT_PATH}/include
	)
	
include(../DownloadProject/DownloadProject.cmake)

#下载googletest
download_project(
    PROJ googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.8.x
    UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

if(MSVC)
	set(CMAKE_CXX_FLAG_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	set(CMAKE_CXX_FLAG_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAG_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
	set(CMAKE_CXX_FLAG_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
endif()

#添加测试
#add_subdirectory(list)
add_subdirectory(sort)