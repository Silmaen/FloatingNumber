# need a recent CMAKE
cmake_minimum_required(VERSION 3.18.0)

# ---=== Project Base ===---
project(FloatingNumber CXX)
set(FLN_ROOT_DIR   "${PROJECT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX ${PROJECT_BUILD_DIR}/Install)
set(CMAKE_CXX_STANDARD 17)

# ---=== Supported OS ===---
if (CMAKE_SYSTEM_NAME MATCHES "OpenBSD")
    message(STATUS "Detected Operating System '${CMAKE_SYSTEM_NAME}'" )
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "Detected Operating System '${CMAKE_SYSTEM_NAME}'" )
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "Detected Operating System '${CMAKE_SYSTEM_NAME}'" )
else()
    message(FATAL_ERROR "Unsupported Operating System '${CMAKE_SYSTEM_NAME}'" )
endif()

# ---=== Build flags ===---
set(CMAKE_CXX_FLAGS "")
# base flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # compiler flags
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(CMAKE_CXX_FLAGS "-g -O0")
    elseif(CMAKE_BUILD_TYPE MATCHES "Small")
        set(CMAKE_CXX_FLAGS "-Os")
    else()
        set(CMAKE_CXX_FLAGS "-O3")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
    #linker flags
    if (CMAKE_SYSTEM_NAME MATCHES "Windows")
        set(CMAKE_EXE_LINKER_FLAGS "-lm -lpthread")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "-lm -lpthread -ldl -lcrypt")
    endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # compiler flags
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(CMAKE_CXX_FLAGS "-g -O0")
    elseif(CMAKE_BUILD_TYPE MATCHES "Small")
        set(CMAKE_CXX_FLAGS "-Os")
    else()
        set(CMAKE_CXX_FLAGS "-O3")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /EHsc /GR /MD /TP /Zc:wchar_t /W4 /GS /Zi /Ob0 /Od /RTC1")
else()
    message( FATAL_ERROR "Unsupported Compiler '${CMAKE_CXX_COMPILER_ID}'" )
endif()

# ---=== Defines ===---
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_definitions(FLN_DEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES "Small")
    add_compile_definitions(FLN_SMALL)
else()
    add_compile_definitions(FLN_RELEASE)
endif()
if (FLN_VERBOSE_TEST)
    add_compile_definitions(FLN_VERBOSE_TEST)
endif()

# ---=== Print Configuration ===---
message(STATUS "Build options are: ${CMAKE_CXX_FLAGS} ${COMPILE_DEFINITIONS}")
message(STATUS  "Link  options are: ${CMAKE_EXE_LINKER_FLAGS}")

# ---=== Unit Tests ===---
enable_testing()
add_subdirectory(test)

# ---=== documentation ===---
find_package(Doxygen
        REQUIRED dot)
if (DOXYGEN_FOUND)
    message(STATUS "found doxygen version: ${DOXYGEN_VERSION}")
    add_custom_target(documentation
            COMMAND ${DOXYGEN_EXECUTABLE}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating API documentation"
            VERBATIM )
else(DOXYGEN_FOUND)
    message(ERROR no doxygen found)
endif(DOXYGEN_FOUND)