#basic 的配置

#基础cpp文件
SET( BASIC_TEST_CPP 
	${PROJECT_SOURCE_DIR}/src/basic 
	)

#头文件设置
SET( BASIC_TEST_H ${PROJECT_SOURCE_DIR}/include	)

#公共库文件
SET(COMMON_CPP ${PROJECT_SOURCE_DIR}/src/common)

FILE(GLOB_RECURSE BASIC_FILE LIST_DIRECTORIES false ${BASIC_TEST_CPP}/*.cpp ${BASIC_TEST_CPP}/*.c ${BASIC_TEST_CPP}/*.h ${BASIC_TEST_H}/*.h)
MESSAGE(STATUS "BASIC_FILE:")
FOREACH(file IN LISTS BASIC_FILE)
	MESSAGE(STATUS ${file})
ENDFOREACH(file)

FILE(GLOB_RECURSE COMMON_FILE LIST_DIRECTORIES false ${COMMON_CPP}/*.cpp)
MESSAGE(STATUS "COMMON_FILE:")
FOREACH(file IN LISTS COMMON_FILE)
	MESSAGE(STATUS ${file})
ENDFOREACH(file)

include_directories(${BASIC_TEST_H})

add_executable(basic_kownledge ${BASIC_FILE} ${COMMON_FILE})
target_link_libraries(basic_kownledge	gtest_main gtest)