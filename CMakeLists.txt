cmake_minimum_required(VERSION 3.20)

project(GonEngine CXX C)
# List of projects
set(PROJECT_LIST

  
    SceneEditor
    Tests
)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Config types" FORCE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Files for dependencies and platform specific config
include(cmake/deps_files.cmake)
include(cmake/platform.cmake)
include(cmake/compiler.cmake)

file(GLOB_RECURSE RECURSIVE_SRC_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/GonEngine/*.cpp
    #${CMAKE_CURRENT_LIST_DIR}/src/GonEngine/*.h
)


file(GLOB_RECURSE RECURSIVE_HEADER_FILES
    ${CMAKE_CURRENT_LIST_DIR}/include/GonEngine/*.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/GonEngine/*.h
    #${CMAKE_CURRENT_LIST_DIR}/include/GonEngine/*.cpp
)

set (ENGINE_SRC_FILES ${RECURSIVE_SRC_FILES})
set (ENGINE_HEADER_FILES ${RECURSIVE_HEADER_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/GonEngine/ PREFIX "Source Files" FILES ${ENGINE_SRC_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include/GonEngine PREFIX "Header Files" FILES ${ENGINE_HEADER_FILES})

add_library(EngineLib STATIC ${ENGINE_SRC_FILES} ${ENGINE_HEADER_FILES} ${DEPS_SRC_FILES_COMMON})


target_include_directories(EngineLib PRIVATE ${INCLUDE_PATHS})

# PCH support
# target_precompile_headers(EngineLib PRIVATE  /include/GonEngine/gonpch.h)

target_compile_definitions(EngineLib PRIVATE -D_GLFW_USE_OPENGL=1)
target_compile_features(EngineLib PRIVATE cxx_std_17)

configure_platform(EngineLib)
configure_compiler(EngineLib)

#Configure All Projects
foreach(PROJECT ${PROJECT_LIST})

    message("Generating Project " ${PROJECT})

    # Root path of the projects
    set(PROJECTS_PATH ${CMAKE_CURRENT_LIST_DIR}/projects)

    # Create Directory and main.cpp
    file(MAKE_DIRECTORY ${PROJECTS_PATH}/${PROJECT})

    message("Generating Files for Project " ${PROJECT})

    # List of files in project
    file(GLOB_RECURSE RECURSIVE_PROJECT_FILES
        ${PROJECTS_PATH}/${PROJECT}/*.cpp
        ${PROJECTS_PATH}/${PROJECT}/*.hpp
    )
    set (FILES_IN_PROJECT ${RECURSIVE_PROJECT_FILES})


    file(TOUCH ${FILES_IN_PROJECT})
    # Create Project and configure
    add_executable(${PROJECT} ${FILES_IN_PROJECT} ${DEPS_SRC_FILES})
    target_include_directories(${PROJECT} PRIVATE ${INCLUDE_PATHS} ${PROJECT_PATHS} ${PROJECT_DEPS_FILES})


    target_compile_definitions(${PROJECT} PRIVATE -D_GLFW_USE_OPENGL=1)

    target_link_libraries(${PROJECT} PRIVATE EngineLib)
    target_compile_features(${PROJECT} PRIVATE cxx_std_17)

    configure_platform(${PROJECT})
    configure_compiler(${PROJECT})

endforeach()
