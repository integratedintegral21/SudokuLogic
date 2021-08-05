# Sudoku Logic
> A c++ library providing features and functionalities handling implementation of Sudoku and Killer Sudoku puzzles.
 ## Table of contents
 * [General Info](#general-information)
 * [Technologies Used](#technologies-used)
 * [Features](#features)
 * [Setup])(#setup)
 * [Usage](#usage)
 ## General Inforamtion
  - The project contains 3 subdirectories: 
    -**library/** - the library's main directory, contains CMakeLists.txt and source files;
    -**test/** - unit tests directory, uses BOOST framework
    -**program/** - a sample program using the library
  - Sudoku Logic library implements logic of Sudoku puzzle - allows to create custom game boards, verifies player's moves and solves Sudoku by means of *pruning* (filling the grid with all allowed numbers, testing every possible case and stopping when solved)
  - The library can be used as a component of a Sudoku application
  - Inspired by a CS assignment - The original project was written in Haskell 
 ## Technologies Used
  - **C++11**
  - **CMake** - version 3.19
  - **BOOST** (only for testing) - version 1.74.0
  - **CLion**
 ## Features
  - Constructing a 9x9 Sudoku game board
  - Applying custom constraints (e.g. Killer Sudoku)
  - Displaying the game board along with numbers inside
  - Determining allowed numbers for every grid's cell
  - Veryfing player's moves
  - A NPC solving the puzzle
 ## Setup   
  PROJECT_DIR - parent directory of downloaded SudokuLogic repo
  ### Requirements 
   - **C++11**
   - **CMake >= 3.4**
   - (Windows only) **Microsoft Visual Studio 2019**
   - (Testing only) BOOST >= 1.60.0
  ### Linux 
  `cd PROJECT_DIR/SudokuLogic/library`
  `cmake .`
  `make`
  Now *libSudokuLogicLibrary.a* and *libSudokuLogicLibrary.so* should be present inside *library/* directory. You can link them to your project with CMake (see #usage section)
  ### Windows
  Open Powershell windows in PROJECT_DIR/SudokuLogic/library
  `cmake .`
  Open .sln file with Visual Studio 2019
  Right panel -> RMB click on ALL_BUILD -> Build
  Now *libSudokuLogicLibrary.lib* and *libSudokuLogicLibrary.dll* are generated in PROJECT_DIR/SudokuLogic/library/Debug
 ## Usage
  ### Linking the library
  Create directory Sudoku
  `mkdir Sudoku && cd Sudoku && git clone https://github.com/integratedintegral21/SudokuLogic.git`
  Copy and paste the *main.cpp* file
  `cp SudokuLogic/program/src/main.cpp`
  The file includes an example of initializing, displaying and solving a Sudoku puzzle. Now it is time to create CMakeLists.txt file
  `touch CMakeLists.txt`
  Open the file in the editor of your choice and paste the following code
  `cmake_minimum_required(VERSION 3.4)	# determines minmum version of cmake	`
  `project(Sudoku)		# creates new project  `
  `set(SOURCE_FILES main.cpp)	# appends the only source file to SOURCE_FILES variable  `
  `find_library(SUDOKU_LIBRARY SudokuLogicLibrary HINTS SudokuLogic/library REQUIRED)	# finds the path to Sudoku Logic`  
  `Library `
  `add_executable(Sudoku ${SOURCE_FILES})		# An executable file 'Sudoku' will be created as a result of compilation of  `
  `SOURCE_FILES`
  `target_link_libraries(Sudoku PUBLIC ${SUDOKU_LIBRARY})		# Link the library to Sudoku`
  `target_include_directories(Sudoku PUBLIC SudokuLogic/library/include)		# To avoid include errors`
  Then compile our mini project
  `cmake .`
  `make`
  And execute the program
  `./Sudoku`
 ## Project Status
  __in progress__
 