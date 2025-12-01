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
    This project depends on the `simulator_libraries` provided by the class. A `Makefile` is included to download them for you.

    * **Linux / macOS:**
        ```bash
        make
        ```
    * **Windows:**
        ```bash
        mingw32-make
        ```
    *(This will create a `simulator_libraries/` folder. This folder is ignored by Git.)*

### 2. Building the Project

We use `CMake` to build the project.

1.  **Create and Enter the Build Directory:**
    ```bash
    mkdir build
    cd build
    ```

2.  **Configure the Project:**
    This generates the necessary build files for your operating system.
    * **Linux / macOS:**
        ```bash
        cmake ..
        ```
    * **Windows:**
        ```bash
        cmake -G "MinGW Makefiles" ..
        ```

3.  **Compile the Code:**
    This command automatically runs the correct build tool (Make, MinGW, etc.) for your system.
    * **Linux / macOS:**
        ```bash
        make
        ```
    * **Windows:**
        ```bash
        cmake --build .
        ```

### 3. Running Your Code

The compiled programs will be placed inside the `build/bin/` directory.

* **Linux / macOS:**
    ```bash
    ./bin/chess_app
    ```

* **Windows:**
    ```powershell
    .\bin\chess_app.exe
    ```

* **To Run Tests:**
    ```bash
    ctest
    ```
