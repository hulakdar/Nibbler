file(GLOB_RECURSE GLOBBED_SOURCES "*.cpp")

add_library(gui_sfml SHARED ${GLOBBED_SOURCES})
set_target_properties(gui_sfml PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
	USE_FOLDERS ON)
target_link_libraries (gui_sfml PRIVATE
	sfml-window
	sfml-graphics
	glm
)

