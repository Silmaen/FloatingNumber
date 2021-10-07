

file(GLOB
    SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

add_executable(fln_unit_test ${SRCS})

# base includes
target_include_directories(fln_unit_test PUBLIC ${FLN_ROOT_DIR}/include)
target_link_libraries(fln_unit_test gtest gtest_main)

add_test(fln_UTests ./fln_unit_test  --gtest_output=xml:test/UTest_Report.xml)
set_tests_properties(fln_UTests PROPERTIES TIMEOUT 3600)

FILE(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

FOREACH(child ${children})
    IF(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
        file(GLOB
             SRCS
             ${CMAKE_CURRENT_SOURCE_DIR}/${child}/*.cpp
             )
        IF("${SRCS} " STREQUAL " ")
            message(STATUS "Test folder '${child}' is empty, skipping")
        ELSE()
            add_executable(fln_${child}_unit_test ${SRCS})
            target_include_directories(fln_${child}_unit_test PUBLIC ${FLN_ROOT_DIR}/include)
            target_link_libraries(fln_${child}_unit_test gtest gtest_main)
            add_test(fln_${child}_UTests ./fln_${child}_unit_test  --gtest_output=xml:test/${child}_UTest_Report.xml)
            set_tests_properties(fln_${child}_UTests PROPERTIES TIMEOUT 3600)
        ENDIF()
    ENDIF()
ENDFOREACH()
