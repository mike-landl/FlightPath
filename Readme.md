[![Build](https://github.com/mike-landl/FlightData/actions/workflows/build.yml/badge.svg)](https://github.com/mike-landl/FlightData/actions/workflows/build.yml)
[![Tests](https://github.com/mike-landl/FlightData/actions/workflows/tests.yml/badge.svg)](https://github.com/mike-landl/FlightData/actions/workflows/tests.yml)
# Flight Data

## About The Project
This project is a C++ port of the final project of the lecture flight-simulation at Graz University of Technology.
It reads a **datalogger file** from the flight simulator and attempts to **reconstruct the flight path using only accelerometer data**.

The output is a **.kml file**, located in the data folder, compatible with Google Earth, allowing you to visualize the reconstructed flight path alongside the original flight path.
For example:
![Example](Example.PNG?raw=true "Example")

## Features
Includes unit tests and GitHub Actions CI integration.

## Usage

### Linux

#### Flight Data Reconstruction
1. clone the repository
    ```sh
    git clone https://github.com/mike-landl/FlightData.git
    ```
2. change directory
    ```sh
    cd FlightData
    ```
3. configure cmake
    ```sh
    cmake --preset release-clang
    ```
4. build with cmake
    ```sh
    cmake --build --preset release-clang --target FlightData
    ```
5. run the binary
    ```sh
    ./build/release/src/FlightData
    ```
6. output is stored in the data folder and can be imported in google earth

#### Manually run unit tests
1. clone and configure repository (see [here](####Flight Data Reconstruction))
2. build tests with cmake
    ```sh
    cmake --build --preset release-clang --target RunTests
    ```
3. change directory
    ```sh
    cd build/release/src/tests
    ```
4. run tests
    ```sh
    ctest
    ```

### Windows
#### Flight Data Reconstruction
1. clone the repository
    ```sh
    git clone https://github.com/mike-landl/FlightData.git
    ```
2. open the folder with visual studio (requires enabled cmake support)
3. build and run from within visual studio
4. output is stored in the data folder and can be imported in google earth

#### Manually run unit tests
You can build and run the tests by selecting the target RunTests within visual studio.

## License

Distributed under the MIT License. See [License.txt](License.txt) for more information.