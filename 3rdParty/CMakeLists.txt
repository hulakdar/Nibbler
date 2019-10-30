find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdParty/sdl2/CMakeLists.txt")
    message(FATAL_ERROR "sdl2 submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdParty/SFML/CMakeLists.txt")
    message(FATAL_ERROR "SFML submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdParty/allegro5/CMakeLists.txt")
    message(FATAL_ERROR "allegro5 submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdParty/glm/CMakeLists.txt")
    message(FATAL_ERROR "glm submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#if(NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdParty/imgui/imgui.h" AND NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdParty/imgui/imgui.cpp")
#   message(FATAL_ERROR "imgui submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
#ndif()


set( BUILD_SHARED_LIBS OFF CACHE BOOL "Build only static libs" )

## glm
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm/)

### SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_BUILD_EXAMPLES FALSE)
set(SFML_BUILD_DOC FALSE)
set(SFML_BUILD_TEST_SUITE FALSE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_AUDIO FALSE)
add_subdirectory( SFML )

## SDL2
set(    SDL_STATIC		TRUE  )
set(    SDL_SHARED		FALSE )
option( SDL_ATOMIC		FALSE )
option( SDL_AUDIO		FALSE )
option( SDL_LOADSO   	FALSE )
option( SDL_FILESYSTEM	FALSE )
option( SDL_DLOPEN 	    FALSE )
add_subdirectory( SDL2 )

option (WANT_PHYSFS FALSE)
option (WANT_AUDIO FALSE)
option (WANT_DEMO FALSE)
option (WANT_DOCS FALSE)
option (WANT_TESTS FALSE)
option (WANT_EXAMPLES FALSE)
add_subdirectory( allegro5 )

## imgui
##add_library (imgui-static STATIC	${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp)
								##target_include_directories(imgui-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/)
								##add_library(imgui::imgui ALIAS imgui-static)

