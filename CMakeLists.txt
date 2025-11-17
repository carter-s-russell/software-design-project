# --- 1. Project & Language Setup ---
# Set the minimum CMake version.
cmake_minimum_required(VERSION 3.15)

# Define the project name and the languages we will use.
# We need CXX (for C++) and C (for the library's tigr.c file).
project(ChessProject LANGUAGES CXX C)

# --- 2. Build Configuration ---
# Enforce the C++17 standard for all C++ code.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Put all final executables (.exe or .out) into a 'bin' folder inside 'build'.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Put all compiled libraries (.a or .so) into a 'lib' folder inside 'build'.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- 3. Find System Libraries (for the FEH Library) ---
# The FEH library (specifically tigr.c) needs OpenGL and X11 to draw windows.
# We find these system libraries here so we can link them later.
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

# Store the found libraries in a variable for convenience.
# On your Fedora machine, this will find opengl, glx, and x11.
set(FEH_SYSTEM_LIBS OpenGL::GL OpenGL::GLX X11::X11)

# --- 4. Define the FEH Class Library (feh_lib) ---
# We define the class's library, "feh_lib", by compiling its source files.
add_library(feh_lib
    "simulator_libraries/FEHLCD.cpp"
    "simulator_libraries/FEHRandom.cpp"
    "simulator_libraries/FEHSD.cpp"
    "simulator_libraries/tigr.c"
    "simulator_libraries/FEHUtility.cpp"
    "simulator_libraries/FEHImages.cpp"
)

# Tell 'feh_lib' where to find its own header files.
target_include_directories(feh_lib PUBLIC
    "simulator_libraries"
)

# Link 'feh_lib' to the system libraries it needs.
# 'PUBLIC' means that any other library that links to 'feh_lib'
# will automatically link to these system libraries too.
target_link_libraries(feh_lib PUBLIC ${FEH_SYSTEM_LIBS})

# --- 5. Define Your Chess Logic Library (chess) ---
# List all the .cpp files for your core game logic.
set(CHESS_SOURCES
    "src/board.cpp"
    # Add new files like "src/piece.cpp" here as you create them
)

# Define your 'chess' library using the source files listed above.
add_library(chess ${CHESS_SOURCES})

# Tell the 'chess' library where to find its own header files (e.g., "include/chess/board.h").
target_include_directories(chess PUBLIC
    "include"
)

# Link your 'chess' library to the 'feh_lib' library.
# This is what lets you use #include "FEHLCD.h" in your game logic files.
target_link_libraries(chess PUBLIC feh_lib)

# --- 6. Define the Main Game Executable (chess_app) ---
# Create the final, runnable program from your main.cpp.
add_executable(chess_app
    "src/main.cpp"
)

# Link the final program against your 'chess' library.
# Because of our 'PUBLIC' links, this one link gives 'chess_app'
# access to 'chess', 'feh_lib', and all the system libraries.
target_link_libraries(chess_app PRIVATE
    chess
)

# --- 7. Define the Test Executable (run_tests) ---
# Turn on CMake's testing features (for CTest).
enable_testing()

# Find all files in your tests/ folder that end in .cpp.
file(GLOB TEST_SOURCES "tests/*.cpp")

# Create the test executable from all the test files.
add_executable(run_tests ${TEST_SOURCES})

# Link the test executable to your 'chess' library.
target_link_libraries(run_tests PRIVATE
    chess
)

# Register 'run_tests' as a test that CTest can run.
add_test(NAME ChessTests COMMAND run_tests)
