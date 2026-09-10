# cmakeversion
cmake_minimum_required(VERSION 3.15)

project(where_the_light_falls LANGUAGES C CXX)

# flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile_commands.json
# i dont remember what we did for microsoft vs solution file, so that for todo:

#debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_MODE=1)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(MSVC)
    add_compile_options(/W4) # windows visual studio equivalent of -Wall
endif()


# main executable target
file(GLOB_RECURSE MY_SRC
	"src/*.cpp"
	"src/*.c"
)

file(GLOB IMGUI_SRC 
    "external/imgui/*.cpp"
)

add_executable( where_the_light_falls
	${MY_SRC}

	external/glad/src/glad.c
	${IMGUI_SRC}
	external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)


target_precompile_headers(where_the_light_falls 
    PRIVATE 
        src/pch.h
)

# infoo: silence warnings from raw external source files compiled in this target
# todo: change the color to something dimmer for info: this shouldnt be here
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set_source_files_properties(
        external/glad/src/glad.c
        ${IMGUI_SRC}
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
        PROPERTIES COMPILE_OPTIONS "-w"
    )
elseif(MSVC)
    set_source_files_properties(
        external/glad/src/glad.c
        ${IMGUI_SRC}
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
        PROPERTIES COMPILE_OPTIONS "/w"
    )
endif()

target_include_directories(where_the_light_falls PRIVATE
	src/
)

target_include_directories(where_the_light_falls SYSTEM PRIVATE 
	external/spdlog/include/
	external/json/ # i made json/json/json.hpp, so i can do include <json/json.hpp> 
	external/glad/include/
	external/glfw/include/
	external/glm/
	external/imgui/
	external/imgui/backends/

)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_INSTALL OFF CACHE INTERNAL "")

add_subdirectory(external/glfw SYSTEM) # system silents the warnings
add_subdirectory(external/spdlog SYSTEM)

target_link_libraries(where_the_light_falls PRIVATE
	glfw 
	spdlog
)

# macro filter bindings
target_compile_definitions(where_the_light_falls PRIVATE
    $<$<CONFIG:Debug>:DEBUG_MODE=1>
    $<$<CONFIG:Release>:RELEASE_MODE=1>
    $<$<CONFIG:Dist>:DIST_MODE=1>
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(where_the_light_falls PRIVATE
        $<$<CONFIG:Debug>:-g -O0>
        $<$<CONFIG:Release>:-O2>
        $<$<CONFIG:Dist>:-O3 -s>
    )
elseif(MSVC)
    target_compile_options(where_the_light_falls PRIVATE
        $<$<CONFIG:Debug>:/Od /Zi>
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:Dist>:/Ox /GL>
    )
endif()

# platform linkages
if(WIN32)
    target_compile_definitions(where_the_light_falls PRIVATE PLATFORM_WINDOWS)
    target_link_libraries(where_the_light_falls PRIVATE gdi32 user32 shell32)
elseif(APPLE)
    target_compile_definitions(where_the_light_falls PRIVATE PLATFORM_MACOS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	# there was some error during my last engine practice with hazel series
	# had to add -pic or something. i dont remember. will figure our once i get an error
    target_compile_definitions(where_the_light_falls PRIVATE PLATFORM_LINUX)
    target_link_libraries(where_the_light_falls PRIVATE pthread dl)
endif()

# asset file copying
add_custom_command(
    TARGET where_the_light_falls POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:where_the_light_falls>/assets"
    COMMENT "Deploying game assets to the build folder..."
)

# configuration summary
message(STATUS "-------------------------------------------------------------")
message(STATUS "  where_the_light_falls - Build Configuration Summary")
message(STATUS "-------------------------------------------------------------")
message(STATUS "  Build Type:       ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler ID:      ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  C++ Standard:     ${CMAKE_CXX_STANDARD}")
message(STATUS "  System Platform:  ${CMAKE_SYSTEM_NAME}")
message(STATUS "-------------------------------------------------------------")
