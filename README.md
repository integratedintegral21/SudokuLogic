# Sudoku Logic
> A c++ library providing features and functionalities handling implementation of Sudoku and Killer Sudoku puzzles.
 ## Table of contents
 * [General Info](#general-information)
 * [Technologies Used](#technologies-used)
 * [Features](#features)
 * [Setup](#setup)
 * [Usage](#usage)
 ## General Information
  - The project contains 3 subdirectories: <br/>
    -**library/** - the library's main directory, contains CMakeLists.txt and source files;<br/>
    -**test/** - unit tests directory, uses BOOST framework<br/>
    -**program/** - a sample program using the library<br/>
  - Sudoku Logic library implements logic of Sudoku puzzle - allows to create custom game boards, verifies player's moves and solves Sudoku by means of *pruning* (filling the grid with all allowed numbers, testing every possible case and stopping when solved)<br/>
  - The library can be used as a component of a Sudoku application<br/>
  - Inspired by a CS assignment - The original project was written in Haskell <br/>
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
  `cd PROJECT_DIR/SudokuLogic/library`<br/>
  `cmake .`<br/>
  `make`<br/>
  Now *libSudokuLogicLibrary.a* and *libSudokuLogicLibrary.so* should be present inside *library/* directory. You can link them to your project with CMake (see (#usage) section)
  ### Windows
  Open Powershell windows in PROJECT_DIR/SudokuLogic/library<br/>
  `cmake .`<br/>
  Open .sln file with Visual Studio 2019<br/>
  Right panel -> RMB click on ALL_BUILD -> Build<br/>
  Now *libSudokuLogicLibrary.lib* and *libSudokuLogicLibrary.dll* are generated in PROJECT_DIR/SudokuLogic/library/Debug<br/>
 ## Usage
  ### Linking the library
  Create directory Sudoku<br/>
  `mkdir Sudoku && cd Sudoku && git clone https://github.com/integratedintegral21/SudokuLogic.git` <br/>
  Build the library (Setup section)<br/>
  Copy and paste the *main.cpp* file<br/>
  `cp SudokuLogic/program/src/main.cpp`<br/>
  The file includes an example of initializing, displaying and solving a Sudoku puzzle. Now it is time to create CMakeLists.txt file<br/>
  `touch CMakeLists.txt`<br/>
  Open the file in the editor of your choice and paste the following code<br/>
  `cmake_minimum_required(VERSION 3.4)	# determines minmum version of cmake	`<br/>
  `project(Sudoku)		# creates new project  `<br/>
  `set(SOURCE_FILES main.cpp)	# appends the only source file to SOURCE_FILES variable  `<br/>
  `find_library(SUDOKU_LIBRARY SudokuLogicLibrary HINTS SudokuLogic/library REQUIRED)	# finds the path to Sudoku Logic Library `<br/>
  `add_executable(Sudoku ${SOURCE_FILES})		# An executable file 'Sudoku' will be created as a result of compilation of  `
  `SOURCE_FILES`<br/>
  `target_link_libraries(Sudoku PUBLIC ${SUDOKU_LIBRARY})		# Link the library to Sudoku`<br/>
  `target_include_directories(Sudoku PUBLIC SudokuLogic/library/include)		# To avoid include errors`<br/>
  Then compile our mini project<br/>
  `cmake .`<br/>
  `make`<br/>
  And execute the program<br/>
  `./Sudoku`<br/>
 ## Project Status
  __in progress__
 ### bugs
  Unicode characters are not displayed in windows console. Avoid using Sudoku::getBoardString() in Windows.
 
