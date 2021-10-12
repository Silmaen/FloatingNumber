# need a recent CMAKE
cmake_minimum_required(VERSION 3.18.0)

# our project
project(FloatingNumber CXX)

set(FLN_ROOT_DIR   "${PROJECT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX ${PROJECT_BUILD_DIR}/Install)
set(CMAKE_CXX_STANDARD 17)

# python interpreter
find_package(Python3 REQUIRED COMPONENTS Interpreter)

if (CMAKE_SYSTEM_NAME MATCHES "OpenBSD")
    message( "Detected Operating System '${CMAKE_SYSTEM_NAME}'" )
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message( "Detected Operating System '${CMAKE_SYSTEM_NAME}'" )
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message( "Detected Operating System '${CMAKE_SYSTEM_NAME}'" )
else()
    message( FATAL_ERROR "Unsupported Operating System '${CMAKE_SYSTEM_NAME}'" )
endif()

# reset all flags only debug is available (restriction from codingame)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "")
#set(CMAKE_VERBOSE_MAKEFILE ON)


# base flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror")
    if (CMAKE_SYSTEM_NAME MATCHES "Windows")
        set(CMAKE_EXE_LINKER_FLAGS "-lm -lpthread")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "-lm -lpthread -ldl -lcrypt")
    endif()
    # TODO: check for AVX capability
    #    add_definitions(-DAVX)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /EHsc /GR /MD /TP /Zc:wchar_t /W4 /GS /Zi /Ob0 /Od /RTC1") # /wd"4251" /wd"4275" /wd"4702"
else()
    message( FATAL_ERROR "Unsupported Compiler '${CMAKE_CXX_COMPILER_ID}'" )
endif()

if (FLN_VERBOSE_TEST)
    add_compile_definitions(FLN_VERBOSE_TEST)
endif()

# build modes
if (FLN_BUILD_TYPE MATCHES "PROFILING")
    message( "Build Mode Default: PROFILING")
    add_definitions(-DLOCAL)
    add_definitions(-DPROFILING)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -fstack-protector-all")
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -fstack-check -fstack-protector-all")
    endif()
elseif (FLN_BUILD_TYPE MATCHES "COVERAGE")
    message( "Build Mode Default: COVERAGE")
    add_definitions(-DLOCAL)
    add_definitions(-DCOVERAGE)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-inline")
    endif()
elseif (FLN_BUILD_TYPE MATCHES "LOCAL")
    add_definitions(-DLOCAL)
    message( "Build Mode Default: LOCAL")
else()
    set(FLN_BUILD_TYPE "SERVER")
    message( "Build Mode Default: SERVER")
endif()

message( "Build options are: ${CMAKE_CXX_FLAGS} ${COMPILE_DEFINITIONS}")
message( "Link  options are: ${CMAKE_EXE_LINKER_FLAGS}")

enable_testing()

# subproject TEST
add_subdirectory(test)

# documentation
find_package(Doxygen
        REQUIRED dot)
if (DOXYGEN_FOUND)
    message(STATUS "found doxygen version: ${DOXYGEN_VERSION}")

    message("Doxygen build started ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Doxyfile")

    add_custom_target(documentation
            COMMAND ${DOXYGEN_EXECUTABLE}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating API documentation"
            VERBATIM )

else(DOXYGEN_FOUND)
    message(ERROR no doxygen found)
endif(DOXYGEN_FOUND)