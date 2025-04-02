[![Build](https://github.com/mike-landl/FlightData/actions/workflows/build.yml/badge.svg)](https://github.com/mike-landl/FlightData/actions/workflows/build.yml)
[![Tests](https://github.com/mike-landl/FlightData/actions/workflows/tests.yml/badge.svg)](https://github.com/mike-landl/FlightData/actions/workflows/tests.yml)
[![C++23 Standard](https://img.shields.io/badge/Standard-C++23-yellow.svg](https://isocpp.org/std/the-standard)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
# Flight Data

## About The Project
This project is a C++ port of the final assignment from the *Flight Simulation* lecture at Graz University of Technology.
It processes a datalogger file from a flight simulator and tries to reconstruct the flight path using only data from the onboard **inertial measurement unit (IMU)**, including body-fixed linear acceleration and angular velocity.

The output is a **`.kml` file** (stored in the `data/` folder) that can be opened in **Google Earth** to visualize the reconstructed flight path alongside the original.

For example:
![Example](Example.PNG)

## Notes
- This repository serves as a demonstration of how I write and structure my C++ code.
- The codebase uses **C++23**, taking advantage of modern language features where it makes sense.
- It also makes use of **trailing return types**, mostly as an experiment to explore their style and usability.

## Features
- 🧪 Unit tests using Catch2 and CTest  
- ⚙️ Cross-platform support (Linux & Windows)  
- 🚀 GitHub Actions CI integration  
- 🌍 `.kml` output for Google Earth visualization  


## Table of Contents
- [Usage](#usage)
  - [Linux](#linux)
    - [Flight Data Reconstruction](#flight-data-reconstruction)
    - [Run Unit Tests](#run-unit-tests)
  - [Windows](#windows)
    - [Flight Data Reconstruction (Windows)](#flight-data-reconstruction-windows)
    - [Run Unit Tests (Windows)](#run-unit-tests-windows)
- [License](#license)

---

## Usage

### Linux

#### Flight Data Reconstruction
1. Clone the repository:
    ```sh
    git clone https://github.com/mike-landl/FlightData.git
    cd FlightData
    ```
2. Configure CMake:
    ```sh
    cmake --preset release-clang
    ```
3. Build the project:
    ```sh
    cmake --build --preset release-clang --target FlightData
    ```
4. Run the binary:
    ```sh
    ./build/release/src/FlightData
    ```
5. The .kml output will be available in the data/ folder and can be imported into Google Earth.

#### Manually run unit tests
1. Ensure the project is configured (see [here](#flight-data-reconstruction))
2. Build the test target:
    ```sh
    cmake --build --preset release-clang --target RunTests
    ```
3. Navigate to the test output directory:
    ```sh
    cd build/release/src/tests
    ```
4. Run the tests:
    ```sh
    ctest
    ```

### Windows
#### Flight Data Reconstruction (Windows)
1. Clone the repository:
    ```sh
    git clone https://github.com/mike-landl/FlightData.git
    ```
2. Open the folder with Visual Studio (ensure CMake support is enabled).
3. Build and run from within Visual Studio.
4. Output is stored in the data/ folder and can be opened with Google Earth.

#### Run Unit Tests (Windows)
Select the RunTests target in Visual Studio and run it.

## License

Distributed under the MIT License. See [License.txt](License.txt) for more information.