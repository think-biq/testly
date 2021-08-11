CMAKE_MINIMUM_REQUIRED (VERSION 3.2)

project (Testly)

file (GLOB Testly_SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c")
set (Testly_INC "${PROJECT_SOURCE_DIR}/src")
include_directories (${Testly_INC})
add_library(Testly ${Testly_SRC})

target_include_directories(
    Testly PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
)

install(
    TARGETS Testly
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/src"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN "*.h"
)

if(Testly_WithTest)
	file(GLOB Testly_Test_SRC	
		"${PROJECT_SOURCE_DIR}/test/*.c"
		"${PROJECT_SOURCE_DIR}/test/**/*.c")
	add_executable (TestlyTest ${Testly_Test_SRC})
	target_link_libraries(TestlyTest Testly)
endif()