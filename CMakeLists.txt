CMAKE_MINIMUM_REQUIRED (VERSION 3.19)

project (Testly)

file (GLOB Testly_SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c")
set (Testly_INC "${PROJECT_SOURCE_DIR}/src")
include_directories (${Testly_INC})
add_library(Testly ${Testly_SRC})

if(Testly_WithTest)
	file(GLOB Testly_Test_SRC	
		"${PROJECT_SOURCE_DIR}/test/*.c"
		"${PROJECT_SOURCE_DIR}/test/**/*.c")
	add_executable (TestlyExample ${Testly_Test_SRC})
	target_link_libraries(TestlyExample Testly)
endif()