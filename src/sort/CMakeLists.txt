#sort µƒ≈‰÷√
set(TEST_CPP
		${PROJECT_SOURCE_DIR}/src/sort/bubblesort.cpp
		)

set (TEST_H
		${PROJECT_SOURCE_DIR}/include/sort.h
		)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(sort ${TEST_CPP} ${TEST_H})
target_link_libraries(sort	gtest gmock)