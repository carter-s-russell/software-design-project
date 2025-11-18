# --- 1. Basic Project Setup ---
# Set the minimum CMake version and define the project name.
# We need CXX (for C++) and C (for the library's tigr.c file).
cmake_minimum_required(VERSION 3.15)
project(ChessProject LANGUAGES CXX C)

# --- 2. Build Configuration ---
# Set the C++ standard to C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Put final executables (like chess_app) in a 'bin' folder inside 'build'.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Put compiled libraries (like libchess.a) in a 'lib' folder inside 'build'.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- 3. Find System Graphics Libraries (for FEH library) ---
# Find the OpenGL and X11 libraries that tigr.c depends on.
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

# Store the found system libraries in a variable for easy use.
set(FEH_SYSTEM_LIBS OpenGL::GL OpenGL::GLX X11::X11)

# --- 4. Define the FEH Class Library (feh_lib) ---
# Create the 'feh_lib' library by compiling all the C/C++ files
# from the simulator_libraries folder.
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
# 'PUBLIC' means anyone who links to 'feh_lib' also links to these.
target_link_libraries(feh_lib PUBLIC ${FEH_SYSTEM_LIBS})

# --- 5. Define Your Chess Logic Library (chess) ---
# List all the .cpp files for your core game logic.
set(CHESS_SOURCES
    "src/Board.cpp"
    "src/Piece.cpp"
    "src/Pawn.cpp"
    "src/King.cpp"
    # Add new files like "src/Rook.cpp" here as you create them
)

# Create the 'chess' library from your source files.
add_library(chess ${CHESS_SOURCES})

# Tell the 'chess' library where to find its own header files (in 'include/').
target_include_directories(chess PUBLIC
    "include"
)

# Link your 'chess' library to 'feh_lib'.
# This lets you use FEH library functions (like FEHImage) in your game logic.
target_link_libraries(chess PUBLIC feh_lib)

# --- 6. Define the Main Game Executable (chess_app) ---
# Create the final, runnable program from your main.cpp file.
add_executable(chess_app
    "src/main.cpp"
)

# Link the final program against your 'chess' library.
# This connects your main.cpp to all your game logic and all the FEH libraries.
target_link_libraries(chess_app PRIVATE
    chess
)

# --- 7. Define the Test Executable (run_tests) ---
# Enable CMake's testing framework (CTest).
enable_testing()

# Find all .cpp files in your 'tests/' folder.
file(GLOB TEST_SOURCES "tests/*.cpp")

# Create the test executable from all your test files.
add_executable(run_tests ${TEST_SOURCES})

# Link the test executable to your 'chess' library.
target_link_libraries(run_tests PRIVATE
    chess
)

# Register 'run_tests' as a test that CTest can run.
add_test(NAME ChessTests COMMAND run_tests)

# --- 8. Copy Resource Files (Images) ---
# This rule copies your 'res' folder into 'build/bin/res'
# so the executable can find your images.

# Define the source (your project's res folder)
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/res)
# Define the destination (inside the build/bin folder)
set(RESOURCE_DEST ${CMAKE_BINARY_DIR}/res)

# Create a command that runs *before* building the app
add_custom_command(
    TARGET chess_app  # Run this command when 'chess_app' is built
    PRE_BUILD         # Run it *before* compilation
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            ${RESOURCE_DIR} ${RESOURCE_DEST}
    COMMENT "Copying resource files to build/bin/res..."
)
