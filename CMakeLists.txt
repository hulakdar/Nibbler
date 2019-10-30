cmake_minimum_required(VERSION 3.14)

project(nibbler LANGUAGES CXX)
add_subdirectory(application)
add_subdirectory(gui_sdl)
target_include_directories(gui_sdl PUBLIC application/public)
add_subdirectory(gui_sfml)
target_include_directories(gui_sfml PUBLIC application/public)

add_executable(${PROJECT_NAME} ${NIBBLER_SOURCES})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_target_properties( ${PROJECT_NAME}  gui_sdl gui_sfml ##gui_allegro
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.."
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.."
)

add_subdirectory(3rdParty)

find_package(OpenGL 4.1 REQUIRED)

if (APPLE)
	target_compile_options(nibbler PRIVATE -Wall -Wextra) ########### TODO -Werror)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
	USE_FOLDERS ON)

target_include_directories(${PROJECT_NAME} PRIVATE application/private)
target_include_directories(${PROJECT_NAME} PUBLIC application/public)

target_link_libraries (${PROJECT_NAME} PRIVATE
	glm
	##imgui::imgui
)

if ( DEBUG )
	add_definitions(-DDEBUG=1)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
