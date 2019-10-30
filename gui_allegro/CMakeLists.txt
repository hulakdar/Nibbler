file(GLOB_RECURSE GLOBBED_SOURCES "*.cpp")

add_library(gui_allegro SHARED ${GLOBBED_SOURCES})
set_target_properties(gui_allegro PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
	USE_FOLDERS ON)
target_link_libraries (gui_allegro PRIVATE
	##allegro-window
	##allegro-graphics
	##glm
)

