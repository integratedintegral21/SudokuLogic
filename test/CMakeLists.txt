cmake_minimum_required(VERSION 3.4)
project(SudokuLibraryTest)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)
find_library(SUDOKU_LIBRARY SudokuLogicLibrary HINTS ../library REQUIRED)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)
set(SOURCE_TEST_FILES
        CellTest.cpp
        CellGroupTests.cpp
        # only for debugging
        ../library/src/GameComponents/Sudoku.cpp
        ../library/src/utils.cpp
        ../library/include/typedefs.h
        ../library/include/utils.h
        ../library/include/GameComponents/GameComponents.h)
set(CMAKE_BUILD_TYPE Debug)
add_executable (LibraryTest ${SOURCE_TEST_FILES} master.cpp)
target_link_libraries (LibraryTest
        ${SUDOKU_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        # uncomment this line in case of undefined reference
        #${Boost_LIBRARY_DIR_RELEASE}/libboost_regex.so
        )
target_include_directories(LibraryTest PUBLIC ../library/include)
add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )
add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})