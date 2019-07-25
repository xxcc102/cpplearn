# serialport 的配置

message(STATUS "project send_msg")

#头文件设置
set (COMMON_HEAD 
	${PROJECT_SOURCE_DIR}/include)

set (SRC_DIR_SEND
	${PROJECT_SOURCE_DIR}/src/serialportsend)
	
set (SRC_DIR_NOV
${PROJECT_SOURCE_DIR}/src/bmwserialport)

file(GLOB_RECURSE COMMON_HEAD_FILE LIST_DIRECTORIES false ${COMMON_HEAD}/*.h)
message(STATUS "COMMON_HEAD:")
foreach(file IN LISTS COMMON_HEAD_FILE)
    message(STATUS ${file})
endforeach(file)

file(GLOB_RECURSE SRC_DIR_NOV_FILE LIST_DIRECTORIES false ${SRC_DIR_NOV}/*.cpp ${SRC_DIR_NOV}/*.h)
message(STATUS "SRC_DIR_NOV_FILE:")

list(REMOVE_ITEM SRC_DIR_NOV_FILE ${SRC_DIR_NOV}/gtest_serial.cpp)

foreach(file IN LISTS SRC_DIR_NOV_FILE)
    message(STATUS ${file})
endforeach(file)

file(GLOB_RECURSE SRC_DIR_SEND_FILE LIST_DIRECTORIES false ${SRC_DIR_SEND}/*.cpp ${SRC_DIR_SEND}/*.h)
message(STATUS "SRC_DIR_SEND_FILE:")
foreach(file IN LISTS SRC_DIR_SEND_FILE)
    message(STATUS ${file})
endforeach(file)

include_directories(${COMMON_HEAD} ${SRC_DIR_NOV})

add_executable(serialsend ${COMMON_HEAD_FILE} ${SRC_DIR_NOV_FILE} ${SRC_DIR_SEND_FILE})

target_link_libraries(serialsend gtest_main gtest)
