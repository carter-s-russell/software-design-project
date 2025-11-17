# FEH Software Design Project
This is the repository for our software design project.

## Getting Started

Follow these instructions to get a local copy of the project up and running on your machine.

### 1. Installation

These steps will clone the repository and download the required class libraries.

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/carter-s-russell/software-design-project.git
    cd software-design-project
    ```

2.  **Download Simulator Libraries:**
    This project depends on the `simulator_libraries` provided by your class. A `Makefile` is included in the root of this project to download them for you.

    Run the following command from the root directory (`SDP/`):
    ```bash
    make
    ```
    This will create a `simulator_libraries/` folder. This folder is in the `.gitignore` and will not be committed to the repository.

### 2. Building the Project

We use `CMake` to build the project. All build commands should be run from a separate `build/` directory.

1.  **Create and Enter the Build Directory:**
    From the root directory, run:
    ```bash
    mkdir build
    cd build
    ```

2.  **Configure the Project (Run CMake):**
    This command tells CMake to read your `CMakeLists.txt` file and generate the build files.
    ```bash
    cmake ..
    ```

3.  **Compile the Code (Run Make):**
    This will compile all your code in `src/`, your tests, and the class libraries, creating the final executables.
    ```bash
    make
    ```

### 3. Running Your Code

The compiled programs will be placed inside the `build/bin/` directory.

* **To Run the Main Chess Game:**
    ```bash
    ./bin/chess_app
    ```

* **To Run Your Tests:**
    From inside the `build/` directory, you can run:
    ```bash
    ctest
    ```
    Or, you can run the test executable directly:
    ```bash
    ./bin/run_tests
    ```
