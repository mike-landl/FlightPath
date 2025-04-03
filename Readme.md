# Flight Path

[![Build](https://github.com/mike-landl/FlightPath/actions/workflows/build.yml/badge.svg)](https://github.com/mike-landl/FlightPath/actions/workflows/build.yml)
[![Tests](https://github.com/mike-landl/FlightPath/actions/workflows/tests.yml/badge.svg)](https://github.com/mike-landl/FlightPath/actions/workflows/tests.yml)
[![C++23 Standard](https://img.shields.io/badge/Standard-C++23-yellow.svg)](https://isocpp.org/std/the-standard)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This project processes a datalogger file from a flight simulator and reconstructs the flight path using only data from the onboard **inertial measurement unit (IMU)**.
(i.e. body-fixed linear acceleration and angular velocity)

The output is a **`.kml` file** (stored in the `data/` folder) that can be opened in **Google Earth** to visualize the reconstructed flight path alongside the original.

For example:
![Example](Example.PNG)

## Notes
- This repository serves as a demonstration of how I write and structure my C++ code and is not feature complete.
- The codebase uses **C++23**, taking advantage of modern language features where it makes sense.
- It also makes use of **trailing return types**, just because I wanted to try them out.

## Features
- ✅ Unit Testing\
Uses Catch2 and CTest for comprehensive test coverage.

- 🖥️ Cross-Platform Support\
Compatible with both Linux and Windows environments.

- 🐳 Docker Support\
Dockerized environment for consistent dependency management and easier setup.

- 🔄 Continuous Integration\
Integrated with GitHub Actions for automatic testing and build verification.

- 📚 Full Documentation\
Generated with Doxygen. Available for download under the Releases section or can be compiled locally.

- 🌍 Google Earth Integration\
Outputs .kml files for visualization in Google Earth.


## Table of Contents
- [Overview](#flight-path)
- [Notes](#notes)
- [Features](#features)
- [Usage](#usage)
  - [Linux](#linux)
    - [Reconstruction](#flight-path-reconstruction)
    - [Unit Tests](#run-unit-tests)
    - [Docker](#docker-support)
    - [Documentation](#build-the-documentation)
  - [Windows](#windows)
    - [Reconstruction](#flight-path-reconstruction-windows)
    - [Unit Tests](#run-unit-tests-windows)
- [License](#license)

---

## Usage

### Linux

#### Flight Path Reconstruction
1. Clone the repository:
    ```sh
    git clone https://github.com/mike-landl/FlightPath.git
    cd FlightPath
    ```
2. Configure the project with CMake
    ```sh
    cmake --preset release-clang
    ```
3. Build the project:
    ```sh
    cmake --build --preset release-clang --target FlightPath
    ```
4. Run the binary:
    ```sh
    ./build/release/src/FlightPath
    ```
5. The .kml output will be available in the data/ folder and can be imported into Google Earth.

#### Run Unit Tests
1. Ensure the project is configured (see [here](#flight-path-reconstruction))
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

### Docker Support

This project includes a Docker setup for consistent builds and easy dependency management.

#### Prerequisites

Make sure Docker and Docker Compose are installed on your system.

- [Docker installation guide](https://docs.docker.com/engine/install/)

- Docker Compose:

```sh
mkdir -p ~/.docker/cli-plugins/
curl -SL https://github.com/docker/compose/releases/latest/download/docker-compose-linux-x86_64 -o ~/.docker/cli-plugins/docker-compose
chmod +x ~/.docker/cli-plugins/docker-compose
```

Add your user to the Docker group to avoid needing `sudo`:

```sh
sudo usermod -aG docker $USER
newgrp docker
```

#### Build & Run

1. Navigate to the `docker/` directory:
   ```sh
   cd docker
   ```

2. Start the Docker container:
   ```sh
   docker compose up --detach
   ```

3. Access the development container with bash:
   ```sh
   docker compose exec flight_path_docker bash
   ```

4. Inside the container, you can run the standard build and test commands as if you were on your local (host) system.

5. When finished, shut down the container:
   ```sh
   docker compose down
   ```

### Build the Documentation
You can build the documentation locally if you prefer.

#### Prerequisites
Make sure you have **Doxygen** and **Graphviz** installed:
```sh
    sudo apt-get install doxygen graphviz -y
```

#### Build Instructions
1. Clone the repository:
    ```sh
    git clone https://github.com/mike-landl/FlightPath.git
    cd FlightPath
    ```

2. Configure the project with CMake
    This step downloads doxygen-awesome-css and generates the Doxyfile from the template (Doxyfile.in):
    ```sh
    cmake --preset release-clang
    ```

3. Generate the documentation using Doxygen:
    ```sh
    doxygen Doxyfile
    ```

4. View the documentation
    Open the generated index.html file in your browser. For example using firefox:
    ```sh
    firefox doxygen/html/index.html
    ```

### Windows
#### Flight Path Reconstruction (Windows)
1. Clone the repository:
    ```sh
    git clone https://github.com/mike-landl/FlightPath.git
    ```
2. Open the folder with Visual Studio (ensure CMake support is enabled).
3. Build and run from within Visual Studio.
4. Output is stored in the data/ folder and can be opened with Google Earth.

#### Run Unit Tests (Windows)
Select the RunTests target in Visual Studio and run it.

## License

Distributed under the MIT License. See [License.txt](License.txt) for more information.