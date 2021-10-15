
file(GLOB_RECURSE
        SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        )

add_library(${CMAKE_PROJECT_NAME}_lib SHARED ${SRCS})

target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC ${FLN_ROOT_DIR}/include)

