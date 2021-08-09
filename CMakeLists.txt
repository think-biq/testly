CMAKE_MINIMUM_REQUIRED (VERSION 3.19)

project (Testly)

file (GLOB Testly_SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c")
include_directories (
	"${PROJECT_SOURCE_DIR}/src")
add_library(Testly ${Testly_SRC})

if(Testly_WithTest)
	file(GLOB Testly_Test_SRC	
		"${PROJECT_SOURCE_DIR}/test/*.c"
		"${PROJECT_SOURCE_DIR}/test/**/*.c")
	add_executable (TestlyExample ${Testly_Test_SRC})
	target_link_libraries(TestlyExample Testly)
endif()