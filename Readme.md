[![Build](https://github.com/mike-landl/FlightData/actions/workflows/build.yml/badge.svg)](https://github.com/mike-landl/FlightData/actions/workflows/build.yml)
[![Tests](https://github.com/mike-landl/FlightData/actions/workflows/tests.yml/badge.svg)](https://github.com/mike-landl/FlightData/actions/workflows/tests.yml)
# Flight Data

## About The Project
This project is a C++ port of the final project of the lecture flight-simulation at Graz University of Technology.
It reads a **datalogger file** from the flight simulator and attempts to **reconstruct the flight path using only accelerometer data**.

The output is a **.kml file**, located in the data folder, compatible with Google Earth, allowing you to visualize the reconstructed flight path alongside the original flight path.
For example:
![Example](Example.PNG?raw=true "Example")

Includes unit tests and GitHub Actions CI integration.

## Usage

### Windows
1. clone the repository
    ```sh
    git clone https://github.com/mike-landl/FlightData.git
    ```
2. open the folder with visual studio (requires enabled cmake support)
3. build from within visual studio

### Linux
1. clone the repository
    ```sh
    git clone https://github.com/mike-landl/FlightData.git
    ```
2. check out the feature branch 'linux'
    ```sh
    git checkout feature/linux
    ```
3. configure cmake
    ```sh
    cmake --preset release-clang
    ```
4. build with ninja
    ```sh
    cd build/release
    ninja
    ```
5. run the binary
    ```sh
    ./Flightdata
    ```

## License

Distributed under the MIT License. See [License.txt](License.txt) for more information.