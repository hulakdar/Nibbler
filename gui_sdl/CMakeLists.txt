file(GLOB_RECURSE GLOBBED_SOURCES "*.cpp")

add_library(gui_sdl SHARED ${GLOBBED_SOURCES})
set_target_properties(gui_sdl PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
	USE_FOLDERS ON)

target_link_libraries (gui_sdl PRIVATE
	SDL2-static
	SDL2_ttf
	glm
)
target_include_directories(gui_sdl PRIVATE
	${CMAKE_SOURCE_DIR}/3rdParty/SDL_ttf
	${CMAKE_SOURCE_DIR}/3rdParty/stbi
)

