cmake_minimum_required(VERSION 3.4)
project(SudokuLibraryTest)
enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)
set(SOURCE_TEST_FILES
        ../library/src/Cell.cpp
        ../library/include/Cell.h
        CellTest.cpp
        ../library/include/typedefs.h
        ../library/src/utils.cpp
        ../library/include/utils.h
        SudokuTest.cpp)
add_executable (LibraryTest ${SOURCE_TEST_FILES} master.cpp)
target_link_libraries (LibraryTest
        SudokuLogicLibrary
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_LIBRARY_DIR_RELEASE}/libboost_regex.so
        )
add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )
add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})