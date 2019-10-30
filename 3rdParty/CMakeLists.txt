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
find_library(FreeType freetype PATHS ${CMAKE_CURRENT_SOURCE_DIR}/SFML/extlibs/libs-osx/Frameworks/)
target_link_libraries(sfml-graphics PRIVATE ${FreeType})
target_include_directories(sfml-graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SDL_ttf/external/freetype-2.9.1/include)

## SDL2
set(    SDL_STATIC		TRUE  )
set(    SDL_SHARED		FALSE )
option( SDL_ATOMIC		FALSE )
option( SDL_AUDIO		FALSE )
add_subdirectory( SDL2 )
add_library(SDL2::SDL2 ALIAS SDL2-static)
add_subdirectory( SDL_image )
target_compile_definitions(SDL2_image PRIVATE -DSDL_IMAGE_USE_COMMON_BACKEND)
add_subdirectory( SDL_ttf )
target_include_directories(SDL2_ttf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SDL_ttf/external/freetype-2.9.1/include)

add_subdirectory( sigil )
target_include_directories(sigil PRIVATE /usr/include/malloc)
## imgui
##add_library (imgui-static STATIC	${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp)
								##target_include_directories(imgui-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/)
								##add_library(imgui::imgui ALIAS imgui-static)

