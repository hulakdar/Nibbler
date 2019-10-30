file(GLOB_RECURSE GLOBBED_SOURCES "*.cpp")

add_library(gui_sigil SHARED ${GLOBBED_SOURCES})
set_target_properties(gui_sigil PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
	USE_FOLDERS ON)

target_include_directories(gui_sigil PRIVATE ${CMAKE_SOURCE_DIR}/3rdParty/sigil/include)
target_link_libraries (gui_sigil PRIVATE
	sigil
	glm
)

