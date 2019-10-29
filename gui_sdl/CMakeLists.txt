file(GLOB_RECURSE GLOBBED_SOURCES "*.cpp")

add_library(gui_sdl SHARED ${GLOBBED_SOURCES})
target_link_libraries (gui_sdl PRIVATE
	SDL2::SDL2
)

