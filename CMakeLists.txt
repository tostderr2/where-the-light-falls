cmake_minimum_required(VERSION 3.15)
project(where_the_light_falls LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Debug Mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_MODE=1)
endif()

#  warning configurations
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(MSVC)
    add_compile_options(/W4) 
endif()

file(GLOB_RECURSE MY_SRC "src/*.cpp" "src/*.c")
file(GLOB IMGUI_SRC "external/imgui/*.cpp")

add_executable(where_the_light_falls 
    ${MY_SRC} 
    external/glad/src/glad.c 
    ${IMGUI_SRC} 
    external/imgui/backends/imgui_impl_glfw.cpp 
    external/imgui/backends/imgui_impl_opengl3.cpp
)

# precompiled headers
target_precompile_headers(where_the_light_falls PRIVATE src/pch.h)

# silence warnings from external library source files
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set_source_files_properties(
        external/glad/src/glad.c ${IMGUI_SRC} 
        external/imgui/backends/imgui_impl_glfw.cpp external/imgui/backends/imgui_impl_opengl3.cpp 
        PROPERTIES COMPILE_OPTIONS "-w"
    )
elseif(MSVC)
    set_source_files_properties(
        external/glad/src/glad.c ${IMGUI_SRC} 
        external/imgui/backends/imgui_impl_glfw.cpp external/imgui/backends/imgui_impl_opengl3.cpp 
        PROPERTIES COMPILE_OPTIONS "/w"
    )
endif()

# target includes
target_include_directories(where_the_light_falls PRIVATE src/)
target_include_directories(where_the_light_falls SYSTEM PRIVATE 
    external/spdlog/include/
    external/json/
    external/glad/include/
    external/glfw/include/
    external/glm/
    external/imgui/
    external/imgui/backends/
)

# configure glfw internal build settings before adding its directory
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_INSTALL OFF CACHE INTERNAL "")

# automatically add subdirectories from your external folder
add_subdirectory(external/glfw SYSTEM) 
add_subdirectory(external/spdlog SYSTEM)

# main linkages
target_link_libraries(where_the_light_falls PRIVATE glfw spdlog)

# configuration macro bindings
target_compile_definitions(where_the_light_falls PRIVATE 
    $<$<CONFIG:Debug>:DEBUG_MODE=1> 
    $<$<CONFIG:Release>:RELEASE_MODE=1> 
    $<$<CONFIG:Dist>:DIST_MODE=1>
)

# optimization flags per target configuration
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

# --- Platform Specific Configurations ---

# 1. windows
if(WIN32)
    target_compile_definitions(where_the_light_falls PRIVATE PLATFORM_WINDOWS)
    target_link_libraries(where_the_light_falls PRIVATE gdi32 user32 shell32)

# 2. macos
elseif(APPLE)
    target_compile_definitions(where_the_light_falls PRIVATE PLATFORM_MACOS)

    # required apple frameworks for opengl & window management
    find_library(COCOA_FRAMEWORK Cocoa REQUIRED)
    find_library(OPENGL_FRAMEWORK OpenGL REQUIRED)
    find_library(IOKIT_FRAMEWORK IOKit REQUIRED)
    find_library(COREVIDEO_FRAMEWORK CoreVideo REQUIRED)

    target_link_libraries(where_the_light_falls PRIVATE 
        ${COCOA_FRAMEWORK}
        ${OPENGL_FRAMEWORK}
        ${IOKIT_FRAMEWORK}
        ${COREVIDEO_FRAMEWORK}
    )

# 3. linux (ubuntu, mint, etc.)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(where_the_light_falls PRIVATE PLATFORM_LINUX)

    # Standard multi-threading and dynamic loading libraries present on all Linux setups
    find_package(Threads REQUIRED)

    target_link_libraries(where_the_light_falls PRIVATE 
        Threads::Threads
        dl
        m
    )
endif()

# asset file copying 
add_custom_command(
    TARGET where_the_light_falls POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:where_the_light_falls>/assets"
    COMMENT "Deploying game assets to the build folder..."
)

# Configuration Summary
message(STATUS "-------------------------------------------------------------")
message(STATUS "  where_the_light_falls - Build Configuration Summary")
message(STATUS "-------------------------------------------------------------")
message(STATUS "  Build Type:      ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler ID:     ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  C++ Standard:    ${CMAKE_CXX_STANDARD}")
message(STATUS "  System Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "-------------------------------------------------------------")
