#serial_nov 的配置
message(STATUS "project serial_nov")

#基础cpp文件
SET( SERIAL_TEST_CPP 
	${PROJECT_SOURCE_DIR}/src/bmwserialport
	)

#头文件设置
SET( SERIAL_TEST_H ${PROJECT_SOURCE_DIR}/include)

#公共库文件
SET(COMMON_CPP ${PROJECT_SOURCE_DIR}/src/common)

FILE(GLOB_RECURSE SERIAL_FILE LIST_DIRECTORIES false ${SERIAL_TEST_CPP}/*.cpp ${SERIAL_TEST_CPP}/*.h ${SERIAL_TEST_H}/*.h)
MESSAGE(STATUS "SERIAL_FILE:")
FOREACH(file IN LISTS SERIAL_FILE)
	MESSAGE(STATUS ${file})
ENDFOREACH(file)

FILE(GLOB_RECURSE COMMON_FILE LIST_DIRECTORIES false ${COMMON_CPP}/*.cpp)
MESSAGE(STATUS "COMMON_FILE:")
FOREACH(file IN LISTS COMMON_FILE)
	MESSAGE(STATUS ${file})
ENDFOREACH(file)

include_directories(${SERIAL_TEST_H})

add_executable(serial_nov ${SERIAL_FILE} ${COMMON_FILE})
target_link_libraries(serial_nov	gtest_main gtest)