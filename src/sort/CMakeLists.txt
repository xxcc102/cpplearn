#sort 的配置

#排序算法cpp文件
SET( SORT_TEST_CPP 
	${PROJECT_SOURCE_DIR}/src/sort 
	)

#头文件设置
SET( SORT_TEST_H 
	${PROJECT_SOURCE_DIR}/include	
	)

#公共库文件
SET(COMMON_CPP ${PROJECT_SOURCE_DIR}/src/common)

FILE(GLOB_RECURSE SORT_FILE LIST_DIRECTORIES false ${SORT_TEST_CPP}/*.cpp ${SORT_TEST_CPP}/*.h ${SORT_TEST_H}/*.h)
MESSAGE(STATUS "SORT_FILE:")
FOREACH(file IN LISTS SORT_FILE)
	MESSAGE(STATUS ${file})
ENDFOREACH(file)

FILE(GLOB_RECURSE COMMON_FILE LIST_DIRECTORIES false ${COMMON_CPP}/*.cpp)
MESSAGE(STATUS "COMMON_FILE:")
FOREACH(file IN LISTS COMMON_FILE)
	MESSAGE(STATUS ${file})
ENDFOREACH(file)

include_directories(${SORT_TEST_H})

add_executable(sort_kinds ${SORT_FILE} ${COMMON_FILE})
target_link_libraries(sort_kinds	gtest_main gtest)