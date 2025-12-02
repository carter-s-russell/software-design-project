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

# --- 3. Find System Graphics Libraries (Cross-Platform) ---
if(WIN32)
    # --- WINDOWS ---
    # Windows uses native OpenGL and GDI (no X11 or GLX needed)
    find_package(OpenGL REQUIRED)
    set(FEH_SYSTEM_LIBS OpenGL::GL)

elseif(APPLE)
    # --- MACOS ---
    # macOS uses Cocoa frameworks
    find_package(OpenGL REQUIRED)
    find_library(COCOA_LIB Cocoa)
    set(FEH_SYSTEM_LIBS OpenGL::GL ${COCOA_LIB})

else()
    # --- LINUX ---
    # Linux needs OpenGL, GLX, and X11
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    set(FEH_SYSTEM_LIBS OpenGL::GL OpenGL::GLX X11::X11)
endif()

# --- 4. Define the FEH Class Library (feh_lib) ---
# Create the 'feh_lib' library by compiling all the C/C++ files
# from the simulator_libraries folder.
add_library(feh_lib
    "simulator_libraries/FEHLCD.cpp"
    "simulator_libraries/FEHRandom.cpp"
    "simulator_libraries/FEHSD.cpp"
    "simulator_libraries/tigr.cpp"
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
file(GLOB_RECURSE CHESS_SOURCES "src/chess/*.cpp")

add_library(chess ${CHESS_SOURCES})
target_include_directories(chess PUBLIC "include")
target_link_libraries(chess PUBLIC feh_lib)

# --- 6. Define Your UI Library (chess_ui) ---
# Create a new library for screens
file(GLOB_RECURSE SCREEN_SOURCES "src/screen/*.cpp")

add_library(chess_ui ${SCREEN_SOURCES})
# It needs to include its own headers
target_include_directories(chess_ui PUBLIC "include")
# It depends on the chess logic library
target_link_libraries(chess_ui PUBLIC chess feh_lib)

# --- 7. Define the Main Game Executable ---
add_executable(chess_app "src/main.cpp")

# Link against the UI library (which brings in 'chess' automatically)
target_link_libraries(chess_app PRIVATE chess_ui)

# --- 8. Define the Test Executable (run_tests) ---
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

# --- 9. Copy Resource Files (Images) ---
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
